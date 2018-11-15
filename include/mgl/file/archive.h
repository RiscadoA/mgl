#ifndef MGL_FILE_ARCHIVE_H
#define MGL_FILE_ARCHIVE_H

#include <mgl/type.h>
#include <mgl/api_utils.h>
#include <mgl/container/iterator.h>
#include <mgl/stream/stream.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/// <summary>
	///		File attributes type.
	/// </summary>
	typedef mgl_u32_t mgl_file_attributes_t;

	/// <summary>
	///		File attributes.
	/// </summary>
	enum 
	{
		MGL_FILE_ATTRIBUTE_FOLDER = 0x01,
	};

#define MGL_FILE_STREAM_AVAILABLE_SIZE 32
	
	typedef struct mgl_archive_functions_t mgl_archive_functions_t;
	typedef struct mgl_archive_base_t mgl_archive_base_t;
	typedef mgl_archive_base_t mgl_archive_t;

	/// <summary>
	///		File stream data.
	/// </summary>
	typedef struct
	{
		mgl_stream_t base;
		mgl_iterator_t file_it;
		mgl_archive_t* archive;
		mgl_u8_t data[MGL_FILE_STREAM_AVAILABLE_SIZE];
	} mgl_file_stream_t;

	/// <summary>
	///		File iterator.
	/// </summary>
	typedef struct
	{
		mgl_archive_t* archive;
	} mgl_file_iterator_t;

#define MGL_FILE_ITERATOR_AVAILABLE_SIZE (MGL_ITERATOR_AVAILABLE_SIZE - sizeof(mgl_file_iterator_t))

	/// <summary>
	///		Archive function table.
	/// </summary>
	struct mgl_archive_functions_t
	{
		mgl_error_t(*file_find)(void* self, const mgl_chr8_t* path, mgl_iterator_t* out);
		mgl_error_t(*file_get_first)(void* self, const mgl_iterator_t* file, mgl_iterator_t* out);
		mgl_error_t(*file_create)(void* self, const mgl_iterator_t* parent, const mgl_chr8_t* name, mgl_file_attributes_t attributes, mgl_iterator_t* out);
		void(*file_delete)(void* self, const mgl_iterator_t* file);
		mgl_error_t(*file_open)(void* self, const mgl_iterator_t* file, mgl_file_stream_t* stream);
		void(*file_close)(void* self, mgl_file_stream_t* stream);
	};

#define MGL_MAX_PATH_SIZE 256
#define MGL_MAX_ARCHIVE_NAME_SIZE 32

	/// <summary>
	///		Archive base structure
	/// </summary>
	struct mgl_archive_base_t
	{
		mgl_chr8_t name[MGL_MAX_ARCHIVE_NAME_SIZE + 1];
		mgl_archive_functions_t* functions;
	};

	/// <summary>
	///		Inits the archive library.
	/// </summary>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_archives_init(void);

	/// <summary>
	///		Terminates the archive library.
	/// </summary>
	void MGL_API mgl_archives_terminate(void);

	/// <summary>
	///		Finds a file given a path.
	///		Paths are formatted as: "[archive-name]/.../.../[file-name]"
	/// </summary>
	/// <param name="path">Path string</param>
	/// <param name="out">Out file iterator</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_file_find(const mgl_chr8_t* path, mgl_iterator_t* out);

	/// <summary>
	///		Gets the first child file in a file.
	/// </summary>
	/// <param name="file">Parent file</param>
	/// <param name="out">Child file</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_file_get_first(const mgl_iterator_t* file, mgl_iterator_t* out);

	/// <summary>
	///		Creates a new file.
	/// </summary>
	/// <param name="parent">Parent file</param>
	/// <param name="name">File name</param>
	/// <param name="attributes">File attributes</param>
	/// <param name="out">Out file iterator (can be NULL)</param>
	/// <returns>
	///		If the file already exists, returns MGL_ERROR_FILE_ALREADY_EXISTS.
	///		Returns MGL_ERROR_UNSUPPORTED_PARENT_ATTRIBUTES if the parent file lacks the MGL_FILE_ATTRIBUTE_FOLDER attribute.
	/// </returns>
	mgl_error_t MGL_API mgl_file_create(const mgl_iterator_t* parent, const mgl_chr8_t* name, mgl_file_attributes_t attributes, mgl_iterator_t* out);

	/// <summary>
	///		Deletes a file and all of its children.
	/// </summary>
	/// <param name="file">File iterator</param>
	void MGL_API mgl_file_delete(const mgl_iterator_t* file);

	/// <summary>
	///		Opens a file stream.
	/// </summary>
	/// <param name="file">File iterator</param>
	/// <param name="stream">Out file stream</param>
	/// <returns>
	///		Returns MGL_ERROR_UNSUPPORTED if the file has the MGL_FILE_ATTRIBUTE_FOLDER attribute.
	/// </returns>
	mgl_error_t MGL_API mgl_file_open(const mgl_iterator_t* file, mgl_file_stream_t* stream);

	/// <summary>
	///		Closes a file stream.
	/// </summary>
	/// <param name="stream">File stream</param>
	void MGL_API mgl_file_close(mgl_file_stream_t* stream);

	/// <summary>
	///		Registers an archive.
	/// </summary>
	/// <param name="name">Archive name</param>
	/// <param name="archive">Archive pointer</param>
	void MGL_API mgl_register_archive(const mgl_chr8_t* name, mgl_archive_t* archive);

	/// <summary>
	///		Unegisters an archive.
	/// </summary>
	/// <param name="archive">Archive pointer</param>
	void MGL_API mgl_unregister_archive(mgl_archive_t* archive);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_FILE_ARCHIVE_H
