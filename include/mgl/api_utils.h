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

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MGL_API_UTILS_H
