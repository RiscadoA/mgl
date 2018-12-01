#ifndef MGL_FILE_WINDOWS_STANDARD_ARCHIVE_H
#define MGL_FILE_WINDOWS_STANDARD_ARCHIVE_H

#include <mgl/file/archive.h>
#include <mgl/container/singly_linked_list.h>
#include <mgl/thread/mutex.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	typedef struct mgl_windows_standard_archive_t mgl_windows_standard_archive_t;
	typedef mgl_archive_base_t mgl_archive_t;

	/// <summary>
	///		Windows standard archive info struct.
	/// </summary>
	struct mgl_windows_standard_archive_t
	{
		mgl_archive_base_t base;
		mgl_chr8_t path[2048];
		mgl_allocator_t* allocator;
		void* root_file;
		mgl_mutex_t mutex;
	};

	/// <summary>
	///		Inits a Windows standard archive.
	/// </summary>
	/// <param name="archive">Archive pointer</param>
	/// <param name="allocator">Allocator pointer</param>
	/// <param name="windows_folder_path">Windows folder path where the archive is located</param>
	/// <returns>Error code</returns>
	mgl_error_t MGL_API mgl_init_windows_standard_archive(mgl_windows_standard_archive_t* archive, mgl_allocator_t* allocator, const mgl_chr8_t* windows_folder_path);

	/// <summary>
	///		Terminates a Windows standard archive.
	/// </summary>
	/// <param name="archive">Archive pointer</param>
	void MGL_API mgl_terminate_windows_standard_archive(mgl_windows_standard_archive_t* archive);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_FILE_WINDOWS_STANDARD_ARCHIVE_H
