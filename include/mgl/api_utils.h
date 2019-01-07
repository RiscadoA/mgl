#ifndef MGL_API_UTILS_H
#define MGL_API_UTILS_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef MGL_API
#	ifdef MGL_BUILD_SHARED
#		ifdef _WIN32
#			ifdef MGL_API_EXPORT
#				define MGL_API __declspec(dllexport)
#			else
#				define MGL_API __declspec(dllimport)
#			endif
#		else
#			define MGL_API
#		endif
#	else
#		define MGL_API
#	endif
#endif 

#ifdef _WIN32
#	define MGL_SYSTEM_WINDOWS
#	undef MGL_SYSTEM_POSIX_COMPATIBLE
#endif

#ifdef __unix__
#	define MGL_SYSTEM_POSIX_COMPATIBLE
#	define MGL_SYSTEM_UNIX
#endif

#ifdef NDEBUG
#define MGL_BUILD_RELEASE
#else
#define MGL_BUILD_DEBUG
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_API_UTILS_H
