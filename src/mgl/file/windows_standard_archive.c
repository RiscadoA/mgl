#include <mgl/file/windows_standard_archive.h>
#include <mgl/string/manipulation.h>
#include <mgl/stream/buffer_stream.h>
#include <mgl/memory/manipulation.h>

#ifdef _WIN32
#include <Windows.h>

typedef struct mgl_windows_standard_archive_file_t mgl_windows_standard_archive_file_t;

struct mgl_windows_standard_archive_file_t
{
	mgl_windows_standard_archive_file_t* parent;
	mgl_windows_standard_archive_file_t* child;
	mgl_windows_standard_archive_file_t* next;
	mgl_chr8_t name[256];
	mgl_file_attributes_t attributes;
};

typedef struct
{
	HANDLE handle;
	mgl_bool_t eof;
} mgl_windows_standard_archive_file_stream_t;

MGL_STATIC_ASSERT(sizeof(mgl_windows_standard_archive_file_stream_t) <= MGL_FILE_STREAM_AVAILABLE_SIZE, u8"File stream is too big");

typedef struct
{
	mgl_file_iterator_t base;
	mgl_windows_standard_archive_file_t* file;
} mgl_windows_standard_archive_file_iterator_t;

static mgl_error_t mgl_windows_standard_archive_stream_write(mgl_stream_t* stream, const void* memory, mgl_u64_t size, mgl_u64_t* out_write_size)
{
	mgl_file_stream_t* fs = (mgl_file_stream_t*)stream;
	mgl_windows_standard_archive_file_stream_t* fsd = (mgl_windows_standard_archive_file_stream_t*)fs->data;

	DWORD written;
	BOOL ret = WriteFile(fsd->handle, memory, (DWORD)size, &written, NULL);
	if (out_write_size != NULL)
		*out_write_size = written;

	if (ret == 0)
		return MGL_ERROR_EXTERNAL;

	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_windows_standard_archive_stream_read(mgl_stream_t* stream, void* memory, mgl_u64_t size, mgl_u64_t* out_read_size)
{
	mgl_file_stream_t* fs = (mgl_file_stream_t*)stream;
	mgl_windows_standard_archive_file_stream_t* fsd = (mgl_windows_standard_archive_file_stream_t*)fs->data;

	DWORD read;
	BOOL ret = ReadFile(fsd->handle, memory, (DWORD)size, &read, NULL);
	if (out_read_size != NULL)
		*out_read_size = read;

	if (ret == 0 || read != size)
	{
		if (GetLastError() == ERROR_HANDLE_EOF || read != size)
		{
			fsd->eof = MGL_TRUE;
			return MGL_ERROR_EOF;
		}
		else
			return MGL_ERROR_EXTERNAL;
	}

	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_windows_standard_archive_stream_flush(mgl_stream_t* stream)
{
	mgl_file_stream_t* fs = (mgl_file_stream_t*)stream;
	mgl_windows_standard_archive_file_stream_t* fsd = (mgl_windows_standard_archive_file_stream_t*)fs->data;
	return (FlushFileBuffers(fsd->handle) == 0) ? MGL_ERROR_EXTERNAL : MGL_ERROR_NONE;
}

static mgl_bool_t mgl_windows_standard_archive_stream_eof(mgl_stream_t* stream)
{
	mgl_file_stream_t* fs = (mgl_file_stream_t*)stream;
	mgl_windows_standard_archive_file_stream_t* fsd = (mgl_windows_standard_archive_file_stream_t*)fs->data;
	return fsd->eof;
}

static mgl_u64_t mgl_windows_standard_archive_stream_tell(mgl_stream_t* stream)
{
	mgl_file_stream_t* fs = (mgl_file_stream_t*)stream;
	mgl_windows_standard_archive_file_stream_t* fsd = (mgl_windows_standard_archive_file_stream_t*)fs->data;
	LARGE_INTEGER li;
	li.QuadPart = 0;
	SetFilePointerEx(fsd->handle, li, &li, FILE_CURRENT);
	return (mgl_u64_t)li.QuadPart;
}

static mgl_error_t mgl_windows_standard_archive_stream_seek(mgl_stream_t* stream, mgl_i64_t position, mgl_enum_t direction)
{
	mgl_file_stream_t* fs = (mgl_file_stream_t*)stream;
	mgl_windows_standard_archive_file_stream_t* fsd = (mgl_windows_standard_archive_file_stream_t*)fs->data;
	if (direction == MGL_STREAM_SEEK_BEGIN)
	{
		LARGE_INTEGER li;
		li.QuadPart = position;
		if (SetFilePointerEx(fsd->handle, li, NULL, FILE_BEGIN) == 0)
		{
			fsd->eof = MGL_TRUE;
			return MGL_ERROR_EOF;
		}
	}
	else if (direction == MGL_STREAM_SEEK_END)
	{
		LARGE_INTEGER li;
		li.QuadPart = position;
		if (SetFilePointerEx(fsd->handle, li, NULL, FILE_END) == 0)
		{
			fsd->eof = MGL_TRUE;
			return MGL_ERROR_EOF;
		}
	}
	else if (direction == MGL_STREAM_SEEK_CURRENT)
	{
		LARGE_INTEGER li;
		li.QuadPart = position;
		if (SetFilePointerEx(fsd->handle, li, NULL, FILE_CURRENT) == 0)
		{
			fsd->eof = MGL_TRUE;
			return MGL_ERROR_EOF;
		}
	}
	fsd->eof = MGL_FALSE;
	return MGL_ERROR_NONE;
}

static mgl_stream_functions_t mgl_windows_standard_archive_stream_functions =
{
	&mgl_windows_standard_archive_stream_write,
	&mgl_windows_standard_archive_stream_read,
	&mgl_windows_standard_archive_stream_flush,
	&mgl_windows_standard_archive_stream_eof,
	&mgl_windows_standard_archive_stream_tell,
	&mgl_windows_standard_archive_stream_tell,
	&mgl_windows_standard_archive_stream_seek,
	&mgl_windows_standard_archive_stream_seek
};

static mgl_error_t mgl_windows_standard_archive_file_iterator_next(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	MGL_DEBUG_ASSERT(it != NULL && out != NULL);

	out->functions = it->functions;

	if (((mgl_windows_standard_archive_file_iterator_t*)it->data)->file == NULL)
	{
		((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = NULL;
		return MGL_ERROR_OUT_OF_BOUNDS;
	}

	((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = ((mgl_windows_standard_archive_file_iterator_t*)it->data)->file->next;
	if (((mgl_windows_standard_archive_file_iterator_t*)out->data)->file == NULL)
		return MGL_ERROR_OUT_OF_BOUNDS;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_windows_standard_archive_file_iterator_prev(const mgl_iterator_t * it, mgl_iterator_t * out)
{
	MGL_DEBUG_ASSERT(it != NULL && out != NULL);

	out->functions = it->functions;

	if (((mgl_windows_standard_archive_file_iterator_t*)it->data)->file == NULL)
	{
		((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = NULL;
		return MGL_ERROR_OUT_OF_BOUNDS;
	}

	((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = ((mgl_windows_standard_archive_file_iterator_t*)it->data)->file->parent;
	if (((mgl_windows_standard_archive_file_iterator_t*)out->data)->file == NULL)
		return MGL_ERROR_OUT_OF_BOUNDS; 
	((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = ((mgl_windows_standard_archive_file_iterator_t*)out->data)->file->child;
	if (((mgl_windows_standard_archive_file_iterator_t*)out->data)->file == ((mgl_windows_standard_archive_file_iterator_t*)it->data)->file)
	{
		((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = NULL;
		return MGL_ERROR_OUT_OF_BOUNDS;
	}
	while (((mgl_windows_standard_archive_file_iterator_t*)out->data)->file->next != ((mgl_windows_standard_archive_file_iterator_t*)it->data)->file)
		((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = ((mgl_windows_standard_archive_file_iterator_t*)out->data)->file->next;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_windows_standard_archive_file_iterator_move(const mgl_iterator_t * it, mgl_iterator_t * out, mgl_i64_t move)
{
	MGL_DEBUG_ASSERT(it != NULL && out != NULL);

	mgl_error_t e;
	if (move > 0)
	{
		mgl_mem_copy(out, it, sizeof(mgl_iterator_t));
		for (mgl_i64_t i = 0; i < move; ++i)
		{
			e = mgl_windows_standard_archive_file_iterator_next(out, out);
			if (e != MGL_ERROR_NONE)
				return e;
		}
	}
	else if (move < 0)
	{
		mgl_mem_copy(out, it, sizeof(mgl_iterator_t));
		for (mgl_i64_t i = 0; i < -move; ++i)
		{
			e = mgl_windows_standard_archive_file_iterator_prev(out, out);
			if (e != MGL_ERROR_NONE)
				return e;
		}
	}
	return MGL_ERROR_NONE;
}

static mgl_bool_t mgl_windows_standard_archive_file_iterator_is_null(const mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(it != NULL);
	return ((mgl_windows_standard_archive_file_iterator_t*)it->data)->file == NULL;
}

static void * mgl_windows_standard_archive_file_iterator_get(const mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(it != NULL);
	MGL_ASSERT(((mgl_windows_standard_archive_file_iterator_t*)it->data)->file != NULL);
	return ((mgl_windows_standard_archive_file_iterator_t*)it->data)->file;
}

static void * mgl_windows_standard_archive_file_iterator_get_raw(const mgl_iterator_t * it)
{
	MGL_DEBUG_ASSERT(it != NULL);
	return ((mgl_windows_standard_archive_file_iterator_t*)it->data)->file;
}

static mgl_iterator_functions_t mgl_windows_standard_archive_file_iterator_functions =
{
	&mgl_windows_standard_archive_file_iterator_next,
	&mgl_windows_standard_archive_file_iterator_prev,
	&mgl_windows_standard_archive_file_iterator_move,
	&mgl_windows_standard_archive_file_iterator_is_null,
	&mgl_windows_standard_archive_file_iterator_get,
	&mgl_windows_standard_archive_file_iterator_get_raw,
};

MGL_STATIC_ASSERT(sizeof(mgl_windows_standard_archive_file_iterator_t) <= MGL_ITERATOR_AVAILABLE_SIZE, u8"Iterator is too big");

static mgl_error_t mgl_windows_standard_archive_file_find(void* self, const mgl_chr8_t* path, mgl_iterator_t* out)
{
	MGL_DEBUG_ASSERT(self != NULL && path != NULL && out != NULL);

	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;

	mgl_buffer_stream_t stream;
	mgl_chr8_t buffer[4096];
	mgl_init_buffer_stream(&stream, buffer, sizeof(buffer));
	mgl_print((mgl_stream_t*)&stream, path);
	mgl_print((mgl_stream_t*)&stream, u8"//");

	mgl_chr8_t name[256] = { 0 };
	mgl_u64_t name_size;

	mgl_windows_standard_archive_file_t* file = (mgl_windows_standard_archive_file_t*)archive->root_file;

	for(;;)
	{
		// Get next file name
		MGL_DEBUG_ASSERT(mgl_read_chars_until((mgl_stream_t*)&stream, name, sizeof(name), &name_size, u8"/") == MGL_ERROR_NONE);

		if (name_size == 0)
			break;

		mgl_windows_standard_archive_file_t* temp_file = file->child;
		
		// Search for file
		for (; temp_file != NULL;)
		{
			if (mgl_str_equal(temp_file->name, name))
				break;
			temp_file = temp_file->next;
		}

		if (temp_file != NULL)
			file = temp_file;
		else
		{
			((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = NULL;
			((mgl_windows_standard_archive_file_iterator_t*)out->data)->base.archive = (mgl_archive_t*)archive;
			out->functions = &mgl_windows_standard_archive_file_iterator_functions;
			return MGL_ERROR_FILE_NOT_FOUND;
		}
	}

	((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = file;
	((mgl_windows_standard_archive_file_iterator_t*)out->data)->base.archive = (mgl_archive_t*)archive;
	out->functions = &mgl_windows_standard_archive_file_iterator_functions;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_windows_standard_archive_file_get_first(void* self, const mgl_iterator_t* file, mgl_iterator_t* out)
{
	MGL_DEBUG_ASSERT(self != NULL && file != NULL && out != NULL);

	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	((mgl_windows_standard_archive_file_iterator_t*)out->data)->base.archive = (mgl_archive_t*)archive;
	if (((mgl_windows_standard_archive_file_iterator_t*)file->data)->file == NULL || ((mgl_windows_standard_archive_file_iterator_t*)file->data)->file->child == NULL)
	{
		((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = NULL;
		return MGL_ERROR_FILE_NOT_FOUND;
	}
	else ((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = ((mgl_windows_standard_archive_file_iterator_t*)file->data)->file->child;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_windows_standard_archive_file_get_parent(void* self, const mgl_iterator_t* file, mgl_iterator_t* out)
{
	MGL_DEBUG_ASSERT(self != NULL && file != NULL && out != NULL);

	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	((mgl_windows_standard_archive_file_iterator_t*)out->data)->base.archive = (mgl_archive_t*)archive;
	if (((mgl_windows_standard_archive_file_iterator_t*)file->data)->file == NULL || ((mgl_windows_standard_archive_file_iterator_t*)file->data)->file->parent == NULL)
	{
		((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = NULL;
		return MGL_ERROR_FILE_NOT_FOUND;
	}
	else ((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = ((mgl_windows_standard_archive_file_iterator_t*)file->data)->file->parent;
	return MGL_ERROR_NONE;
}

static mgl_error_t mgl_windows_standard_archive_file_create(void* self, const mgl_iterator_t* parent, const mgl_chr8_t* name, mgl_file_attributes_t attributes, mgl_iterator_t* out)
{
	MGL_DEBUG_ASSERT(self != NULL && parent != NULL && name != NULL && !(attributes & MGL_FILE_ATTRIBUTE_ARCHIVE));
	
	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	
	mgl_chr8_t path[4096] = { 0 };
	{
		mgl_buffer_stream_t stream;
		mgl_init_buffer_stream(&stream, path, sizeof(path));

		mgl_print((mgl_stream_t*)&stream, archive->path);
		mgl_print((mgl_stream_t*)&stream, u8"\\");

		mgl_windows_standard_archive_file_t* sequence[256] = { NULL };
		mgl_windows_standard_archive_file_t* file = ((mgl_windows_standard_archive_file_iterator_t*)parent->data)->file;
		mgl_u64_t file_count;
		for (file_count = 0; file->parent != NULL && file_count < 256; ++file_count)
		{
			sequence[file_count] = file;
			file = file->parent;
		} 

		for (mgl_u64_t i = 0; i < file_count; ++i)
		{
			mgl_print((mgl_stream_t*)&stream, sequence[file_count - i - 1]->name);
			mgl_print((mgl_stream_t*)&stream, u8"\\");
		}

		mgl_print((mgl_stream_t*)&stream, name);
	}

	if (attributes & MGL_FILE_ATTRIBUTE_FOLDER) // Folder
	{
		if (CreateDirectoryA(path, NULL) == 0)
		{
			if (GetLastError() == ERROR_ALREADY_EXISTS)
				return MGL_ERROR_FILE_ALREADY_EXISTS;
			return MGL_ERROR_EXTERNAL;
		}
	}
	else // File
	{
		HANDLE file_h = CreateFileA(path, 0, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		if (file_h == INVALID_HANDLE_VALUE)
		{
			if (GetLastError() == ERROR_FILE_EXISTS)
				return MGL_ERROR_FILE_ALREADY_EXISTS;
			return MGL_ERROR_EXTERNAL;
		}
		CloseHandle(file_h);
	}

	mgl_windows_standard_archive_file_t* new_file;
	MGL_DEBUG_ASSERT(mgl_allocate(archive->allocator, sizeof(*new_file), &new_file) == MGL_ERROR_NONE);
	new_file->attributes = attributes;
	new_file->child = NULL;
	new_file->parent = ((mgl_windows_standard_archive_file_iterator_t*)parent->data)->file;
	new_file->next = ((mgl_windows_standard_archive_file_iterator_t*)parent->data)->file->child;
	((mgl_windows_standard_archive_file_iterator_t*)parent->data)->file->child = new_file;
	mgl_str_copy(name, new_file->name, sizeof(new_file->name));

	if (out != NULL)
	{
		((mgl_windows_standard_archive_file_iterator_t*)out->data)->base.archive = (mgl_archive_t*)archive;
		((mgl_windows_standard_archive_file_iterator_t*)out->data)->file = new_file;
		out->functions = parent->functions;
	}

	return MGL_ERROR_NONE;
}

static void mgl_windows_standard_archive_file_delete(void* self, const mgl_iterator_t* it)
{
	MGL_DEBUG_ASSERT(self != NULL && it != NULL);

	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	mgl_windows_standard_archive_file_t* file = ((mgl_windows_standard_archive_file_iterator_t*)it->data)->file;
	
	MGL_ASSERT(file->parent != NULL && !(file->attributes & MGL_FILE_ATTRIBUTE_ARCHIVE));

	// Delete children
	{
		mgl_windows_standard_archive_file_t* child = file->child;
		while (child != NULL)
		{
			mgl_windows_standard_archive_file_t* next = child->next;
			mgl_iterator_t child_it;
			((mgl_windows_standard_archive_file_iterator_t*)child_it.data)->base.archive = (mgl_archive_t*)archive;
			((mgl_windows_standard_archive_file_iterator_t*)child_it.data)->file = child;
			child_it.functions = it->functions;
			mgl_windows_standard_archive_file_delete(self, &child_it);
			child = next;
		}
	}

	mgl_chr8_t path[4096] = { 0 };
	{
		mgl_buffer_stream_t stream;
		mgl_init_buffer_stream(&stream, path, sizeof(path));

		mgl_print((mgl_stream_t*)&stream, archive->path);
		mgl_print((mgl_stream_t*)&stream, u8"\\");

		mgl_windows_standard_archive_file_t* sequence[256] = { NULL };
		mgl_windows_standard_archive_file_t* file_temp = file->parent;
		mgl_u64_t file_count;
		for (file_count = 0; file_temp->parent != NULL && file_count < 256; ++file_count)
		{
			sequence[file_count] = file_temp;
			file_temp = file_temp->parent;
		}

		for (mgl_u64_t i = 0; i < file_count; ++i)
		{
			mgl_print((mgl_stream_t*)&stream, sequence[file_count - i - 1]->name);
			mgl_print((mgl_stream_t*)&stream, u8"\\");
		}

		mgl_print((mgl_stream_t*)&stream, file->name);
	}

	// Delete file
	if (file == file->parent->child)
		file->parent->child = file->next;
	if (file->attributes & MGL_FILE_ATTRIBUTE_FOLDER)
		MGL_DEBUG_ASSERT(RemoveDirectoryA(path) != 0);
	else
		MGL_DEBUG_ASSERT(DeleteFileA(path) != 0);
	MGL_DEBUG_ASSERT(mgl_deallocate(archive->allocator, file) == MGL_ERROR_NONE);
}

static mgl_error_t mgl_windows_standard_archive_file_open(void* self, const mgl_iterator_t* file, mgl_file_stream_t* stream, mgl_file_access_t access)
{
	MGL_DEBUG_ASSERT(self != NULL && file != NULL && stream != NULL);
	MGL_DEBUG_ASSERT(!(((mgl_windows_standard_archive_file_iterator_t*)file->data)->file->attributes & MGL_FILE_ATTRIBUTE_FOLDER) &&
					 !(((mgl_windows_standard_archive_file_iterator_t*)file->data)->file->attributes & MGL_FILE_ATTRIBUTE_ARCHIVE));

	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	
	stream->archive = (mgl_archive_t*)archive;
	stream->base.functions = &mgl_windows_standard_archive_stream_functions;
	mgl_mem_copy(&stream->file_it, file, sizeof(*file));

	mgl_chr8_t path[4096] = { 0 };
	{
		mgl_buffer_stream_t stream;
		mgl_init_buffer_stream(&stream, path, sizeof(path));

		mgl_print((mgl_stream_t*)&stream, archive->path);
		mgl_print((mgl_stream_t*)&stream, u8"\\");

		mgl_windows_standard_archive_file_t* sequence[256] = { NULL };
		mgl_windows_standard_archive_file_t* file_temp = ((mgl_windows_standard_archive_file_iterator_t*)file->data)->file->parent;
		mgl_u64_t file_count;
		for (file_count = 0; file_temp->parent != NULL && file_count < 256; ++file_count)
		{
			sequence[file_count] = file_temp;
			file_temp = file_temp->parent;
		}

		for (mgl_u64_t i = 0; i < file_count; ++i)
		{
			mgl_print((mgl_stream_t*)&stream, sequence[file_count - i - 1]->name);
			mgl_print((mgl_stream_t*)&stream, u8"\\");
		}

		mgl_print((mgl_stream_t*)&stream, ((mgl_windows_standard_archive_file_iterator_t*)file->data)->file->name);
	}

	DWORD access_win = 0;
	if (access & MGL_FILE_READ)
		access_win |= GENERIC_READ;
	if (access & MGL_FILE_WRITE)
		access_win |= GENERIC_WRITE;

	HANDLE handle = CreateFileA(path, access_win, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (handle == INVALID_HANDLE_VALUE)
		return MGL_ERROR_EXTERNAL;
	((mgl_windows_standard_archive_file_stream_t*)stream->data)->handle = handle;

	return MGL_ERROR_NONE;
}

static void mgl_windows_standard_archive_file_close(void* self, mgl_file_stream_t* stream)
{
	MGL_DEBUG_ASSERT(self != NULL && stream != NULL);
	
	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	
	CloseHandle(((mgl_windows_standard_archive_file_stream_t*)stream->data)->handle);

	stream->archive = NULL;
	stream->base.functions = NULL;
	stream->file_it.functions = NULL;
	((mgl_windows_standard_archive_file_stream_t*)stream->data)->handle = NULL;
}

static mgl_file_attributes_t mgl_windows_standard_archive_file_get_attributes(void* self, const mgl_iterator_t* file)
{
	MGL_DEBUG_ASSERT(file != NULL && ((mgl_windows_standard_archive_file_iterator_t*)file->data)->file != NULL);
	return ((mgl_windows_standard_archive_file_iterator_t*)file->data)->file->attributes;
}

static const mgl_chr8_t* mgl_windows_standard_archive_file_get_name(void* self, const mgl_iterator_t* file)
{
	MGL_DEBUG_ASSERT(file != NULL && ((mgl_windows_standard_archive_file_iterator_t*)file->data)->file != NULL);
	return ((mgl_windows_standard_archive_file_iterator_t*)file->data)->file->name;
}

static mgl_archive_functions_t mgl_windows_standard_archive_functions =
{
	&mgl_windows_standard_archive_file_find,
	&mgl_windows_standard_archive_file_get_first,
	&mgl_windows_standard_archive_file_get_parent,
	&mgl_windows_standard_archive_file_create,
	&mgl_windows_standard_archive_file_delete,
	&mgl_windows_standard_archive_file_open,
	&mgl_windows_standard_archive_file_close,
	&mgl_windows_standard_archive_file_get_attributes,
	&mgl_windows_standard_archive_file_get_name
};

static mgl_error_t mgl_windows_standard_archive_recursive_add_folder(mgl_windows_standard_archive_t* archive, const mgl_chr8_t * path, mgl_windows_standard_archive_file_t* parent)
{
	WIN32_FIND_DATAA ffd;
	HANDLE* hFind;
	{
		mgl_chr8_t find_path[4096] = { 0 };
		mgl_buffer_stream_t stream;
		mgl_init_buffer_stream(&stream, find_path, sizeof(find_path));
		mgl_print((mgl_stream_t*)&stream, path);
		mgl_print((mgl_stream_t*)&stream, u8"\\*");
		hFind = FindFirstFileA(find_path, &ffd);
		if (hFind == INVALID_HANDLE_VALUE)
			return MGL_ERROR_EXTERNAL;
	}

	mgl_windows_standard_archive_file_t* prev_file = NULL;

	do
	{
		if (mgl_str_equal(ffd.cFileName, u8".") || mgl_str_equal(ffd.cFileName, u8".."))
			continue;

		mgl_windows_standard_archive_file_t* new_file;
		mgl_error_t e = mgl_allocate(archive->allocator, sizeof(mgl_windows_standard_archive_file_t), &new_file);
		if (e != MGL_ERROR_NONE)
			return e;

		new_file->parent = parent;
		new_file->child = NULL;
		new_file->next = NULL;
		new_file->attributes = 0;
		mgl_str_copy(ffd.cFileName, new_file->name, sizeof(new_file->name));

		if (prev_file != NULL)
			prev_file->next = new_file;
		prev_file = new_file;

		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			new_file->attributes |= MGL_FILE_ATTRIBUTE_FOLDER;
			// Recurse this function again
			mgl_chr8_t folder_path[4096] = { 0 };
			mgl_buffer_stream_t stream;
			mgl_init_buffer_stream(&stream, folder_path, sizeof(folder_path));
			mgl_print((mgl_stream_t*)&stream, path);
			mgl_print((mgl_stream_t*)&stream, u8"\\");
			mgl_print((mgl_stream_t*)&stream, ffd.cFileName);
			e = mgl_windows_standard_archive_recursive_add_folder(archive, folder_path, new_file);
			if (e != MGL_ERROR_NONE)
				return e;
		}

		if (parent->child == NULL)
			parent->child = new_file;
	} while (FindNextFileA(hFind, &ffd) != 0);

	if (GetLastError() != ERROR_NO_MORE_FILES)
		return MGL_ERROR_EXTERNAL;

	FindClose(hFind);
	return MGL_ERROR_NONE;
}

mgl_error_t MGL_API mgl_init_windows_standard_archive(mgl_windows_standard_archive_t * archive, mgl_allocator_t* allocator, const mgl_chr8_t * windows_folder_path)
{
	MGL_DEBUG_ASSERT(archive != NULL && windows_folder_path != NULL);

	archive->allocator = allocator;
	archive->base.functions = &mgl_windows_standard_archive_functions;
	mgl_str_copy(windows_folder_path, archive->path, sizeof(archive->path));
	mgl_error_t e = mgl_allocate(allocator, sizeof(mgl_windows_standard_archive_file_t), &archive->root_file);
	if (e != MGL_ERROR_NONE)
		return e;

	((mgl_windows_standard_archive_file_t*)archive->root_file)->parent = NULL;
	((mgl_windows_standard_archive_file_t*)archive->root_file)->child = NULL;
	((mgl_windows_standard_archive_file_t*)archive->root_file)->next = NULL;
	((mgl_windows_standard_archive_file_t*)archive->root_file)->attributes = MGL_FILE_ATTRIBUTE_ARCHIVE;
	mgl_str_copy(u8"root", ((mgl_windows_standard_archive_file_t*)archive->root_file)->name, sizeof(((mgl_windows_standard_archive_file_t*)archive->root_file)->name));

	// Search for files in the archive folder
	e = mgl_windows_standard_archive_recursive_add_folder(archive, windows_folder_path, (mgl_windows_standard_archive_file_t*)archive->root_file);
	if (e != MGL_ERROR_NONE)
		goto error_cleanup_1;

	return MGL_ERROR_NONE;

error_cleanup_1:
	mgl_deallocate(allocator, archive->root_file);
	return e;
}

void MGL_API mgl_terminate_windows_standard_archive(mgl_windows_standard_archive_t * archive)
{
	mgl_windows_standard_archive_file_t* file = (mgl_windows_standard_archive_file_t*)archive->root_file;
	while (file != NULL)
	{
		while (file->child != NULL)
			file = file->child;
		mgl_windows_standard_archive_file_t* next = file->next;
		if (next == NULL)
		{
			next = file->parent;
			if (next != NULL)
				next = next->next;
		}

		mgl_deallocate(archive->allocator, file);
		file = next;
	}
	archive->base.functions = NULL;
}

#endif