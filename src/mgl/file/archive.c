#include <mgl/file/archive.h>
#include <mgl/memory/manipulation.h>
#include <mgl/string/manipulation.h>
#include <mgl/stream/buffer_stream.h>
#include <mgl/container/singly_linked_list.h>
#include <mgl/thread/mutex.h>

static mgl_singly_linked_list_t mgl_archive_list;
static mgl_mutex_t mgl_archive_list_mutex;

mgl_error_t MGL_API mgl_archives_init(void)
{
	mgl_init_singly_linked_list(&mgl_archive_list, sizeof(mgl_archive_t*), mgl_standard_allocator);
	return mgl_create_mutex(&mgl_archive_list_mutex);
}

void MGL_API mgl_archives_terminate(void)
{
	MGL_ASSERT(mgl_destroy_mutex(&mgl_archive_list_mutex) == MGL_ERROR_NONE);
	mgl_terminate_singly_linked_list(&mgl_archive_list);
}

mgl_error_t MGL_API mgl_file_find(const mgl_chr8_t * path, mgl_iterator_t * out)
{
	MGL_DEBUG_ASSERT(path != NULL);

	mgl_chr8_t archive_name_buffer[MGL_MAX_ARCHIVE_NAME_SIZE + 1];
	mgl_mem_set(archive_name_buffer, sizeof(archive_name_buffer), 0);

	mgl_buffer_stream_t buffer_stream;
	mgl_init_buffer_stream(&buffer_stream, archive_name_buffer, MGL_MAX_ARCHIVE_NAME_SIZE);
	mgl_print((mgl_stream_t*)&buffer_stream, path);

	mgl_chr8_t archive_name[MGL_MAX_ARCHIVE_NAME_SIZE + 1];
	mgl_mem_set(archive_name, sizeof(archive_name), 0);
	mgl_read_chars_until((mgl_stream_t*)&buffer_stream, archive_name, sizeof(archive_name), NULL, u8"/");

	mgl_chr8_t archive_path[MGL_MAX_PATH_SIZE + 1];
	mgl_read((mgl_stream_t*)&buffer_stream, archive_path, sizeof(archive_path), NULL);

	mgl_iterator_t it;
	MGL_DEBUG_ASSERT(mgl_lock_mutex(&mgl_archive_list_mutex) == MGL_ERROR_NONE);
	mgl_get_singly_linked_list_begin_it(&mgl_archive_list, &it);
	for (;;)
	{
		if (mgl_iterator_is_null(&it))
		{
			MGL_DEBUG_ASSERT(mgl_unlock_mutex(&mgl_archive_list_mutex) == MGL_ERROR_NONE);
			return MGL_ERROR_ARCHIVE_NOT_FOUND;
		}
		else
		{
			if (mgl_str_equal(archive_name, (*(mgl_archive_t**)mgl_iterator_get(&it))->name))
			{
				mgl_archive_t* archive = *(mgl_archive_t**)mgl_iterator_get(&it);
				mgl_error_t e = archive->functions->file_find(archive, archive_path, out);
				MGL_DEBUG_ASSERT(mgl_unlock_mutex(&mgl_archive_list_mutex) == MGL_ERROR_NONE);
				return e;
			}
			mgl_iterator_next(&it, &it);
		}
	}
}

mgl_error_t MGL_API mgl_file_get_first(const mgl_iterator_t * file, mgl_iterator_t * out)
{
	MGL_DEBUG_ASSERT(file != NULL);
	return ((mgl_file_iterator_t*)file->data)->archive->functions->file_get_first(((mgl_file_iterator_t*)file->data)->archive, file, out);
}

mgl_error_t MGL_API mgl_file_create(const mgl_iterator_t * parent, const mgl_chr8_t * name, mgl_file_attributes_t attributes, mgl_iterator_t * out)
{
	MGL_DEBUG_ASSERT(parent != NULL);
	return ((mgl_file_iterator_t*)parent->data)->archive->functions->file_create(((mgl_file_iterator_t*)parent->data)->archive, parent, name, attributes, out);
}

mgl_file_attributes_t MGL_API mgl_file_get_attributes(const mgl_iterator_t * file)
{
	MGL_DEBUG_ASSERT(file != NULL);
	return ((mgl_file_iterator_t*)file->data)->archive->functions->file_get_attributes(((mgl_file_iterator_t*)file->data)->archive, file);
}

const mgl_chr8_t *MGL_API mgl_file_get_name(const mgl_iterator_t * file)
{
	MGL_DEBUG_ASSERT(file != NULL);
	return ((mgl_file_iterator_t*)file->data)->archive->functions->file_get_name(((mgl_file_iterator_t*)file->data)->archive, file);
}

void MGL_API mgl_file_delete(const mgl_iterator_t * file)
{
	MGL_DEBUG_ASSERT(file != NULL);
	((mgl_file_iterator_t*)file->data)->archive->functions->file_delete(((mgl_file_iterator_t*)file->data)->archive, file);
}

mgl_error_t MGL_API mgl_file_open(const mgl_iterator_t * file, mgl_file_stream_t * stream)
{
	MGL_DEBUG_ASSERT(file != NULL);
	return ((mgl_file_iterator_t*)file->data)->archive->functions->file_open(((mgl_file_iterator_t*)file->data)->archive, file, stream);
}

void MGL_API mgl_file_close(mgl_file_stream_t * stream)
{
	MGL_DEBUG_ASSERT(stream != NULL);
	stream->archive->functions->file_close(stream->archive, stream);
}

void MGL_API mgl_register_archive(const mgl_chr8_t * name, mgl_archive_t * archive)
{
	MGL_DEBUG_ASSERT(archive != NULL && name != NULL);
	MGL_DEBUG_ASSERT(mgl_lock_mutex(&mgl_archive_list_mutex) == MGL_ERROR_NONE);
	mgl_str_copy(name, archive->name, MGL_MAX_ARCHIVE_NAME_SIZE + 1);
	MGL_DEBUG_ASSERT(mgl_singly_linked_list_push_end(&mgl_archive_list, &archive, NULL) == MGL_ERROR_NONE);
	MGL_DEBUG_ASSERT(mgl_unlock_mutex(&mgl_archive_list_mutex) == MGL_ERROR_NONE);
}

void MGL_API mgl_unregister_archive(mgl_archive_t * archive)
{
	MGL_DEBUG_ASSERT(archive != NULL);
	MGL_DEBUG_ASSERT(mgl_lock_mutex(&mgl_archive_list_mutex) == MGL_ERROR_NONE);
	mgl_iterator_t it;
	mgl_get_singly_linked_list_begin_it(&mgl_archive_list, &it);
	for (;;)
	{
		if (*(mgl_archive_t**)mgl_iterator_get(&it) == archive)
		{
			mgl_singly_linked_list_remove(&mgl_archive_list, &it);
			break;
		}
		MGL_ASSERT(mgl_iterator_next(&it, &it) == MGL_ERROR_NONE); // Archive not registered
	}
	MGL_DEBUG_ASSERT(mgl_unlock_mutex(&mgl_archive_list_mutex) == MGL_ERROR_NONE);
}
