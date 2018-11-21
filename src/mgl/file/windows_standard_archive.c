#include <mgl/file/windows_standard_archive.h>
#include <mgl/string/manipulation.h>
#include <mgl/stream/buffer_stream.h>

#ifdef _WIN32
#include <Windows.h>

typedef struct
{
	mgl_file_iterator_t base;
} mgl_windows_standard_archive_file_iterator_t;

typedef struct mgl_windows_standard_archive_file_t mgl_windows_standard_archive_file_t;

struct mgl_windows_standard_archive_file_t
{
	mgl_windows_standard_archive_file_t* parent;
	mgl_windows_standard_archive_file_t* child;
	mgl_windows_standard_archive_file_t* next;
	mgl_chr8_t name[256];
	mgl_file_attributes_t attributes;
};

MGL_STATIC_ASSERT(sizeof(mgl_windows_standard_archive_file_iterator_t) <= MGL_ITERATOR_AVAILABLE_SIZE, u8"Iterator is too big");

typedef struct
{
	HANDLE file;
} mgl_windows_standard_archive_file_stream_t;

MGL_STATIC_ASSERT(sizeof(mgl_windows_standard_archive_file_stream_t) <= MGL_FILE_STREAM_AVAILABLE_SIZE, u8"File stream is too big");

static mgl_error_t mgl_windows_standard_archive_file_find(void* self, const mgl_chr8_t* path, mgl_iterator_t* out)
{
	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;

	

	return MGL_ERROR_NONE; // TO DO
}

static mgl_error_t mgl_windows_standard_archive_file_get_first(void* self, const mgl_iterator_t* file, mgl_iterator_t* out)
{
	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	
	return MGL_ERROR_NONE; // TO DO
}

static mgl_error_t mgl_windows_standard_archive_file_get_parent(void* self, const mgl_iterator_t* file, mgl_iterator_t* out)
{
	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	
	return MGL_ERROR_NONE; // TO DO
}

static mgl_error_t mgl_windows_standard_archive_file_create(void* self, const mgl_iterator_t* parent, const mgl_chr8_t* name, mgl_file_attributes_t attributes, mgl_iterator_t* out)
{
	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	
	return MGL_ERROR_NONE; // TO DO
}

static void mgl_windows_standard_archive_file_delete(void* self, const mgl_iterator_t* file)
{
	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	
	// TO DO
}

static mgl_error_t mgl_windows_standard_archive_file_open(void* self, const mgl_iterator_t* file, mgl_file_stream_t* stream)
{
	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	
	return MGL_ERROR_NONE; // TO DO
}

static void mgl_windows_standard_archive_file_close(void* self, mgl_file_stream_t* stream)
{
	mgl_windows_standard_archive_t* archive = (mgl_windows_standard_archive_t*)self;
	
	// TO DO
}

static mgl_file_attributes_t mgl_windows_standard_archive_file_get_attributes(void* self, const mgl_iterator_t* file)
{
	return 0; // TO DO	
}

static const mgl_chr8_t* mgl_windows_standard_archive_file_get_name(void* self, const mgl_iterator_t* file)
{
	return NULL; // TO DO
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
	archive->base.functions = NULL;
}

#endif