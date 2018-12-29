# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.11)
project(libmgl VERSION 0.1.0 LANGUAGES C)
include(CTest)
include(GenerateExportHeader)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#####################################################
# MGL source and include files

set(MGL_SOURCE
	"src/mgl/entry.c"
	"src/mgl/error.c"
	"src/mgl/memory/manipulation.c"
	"src/mgl/memory/crc.c"
	"src/mgl/memory/allocator.c"
	"src/mgl/memory/linear_allocator.c"
	"src/mgl/memory/stack_allocator.c"
	"src/mgl/memory/pool_allocator.c"
	"src/mgl/memory/debug_allocator.c"
	"src/mgl/stream/stream.c"
	"src/mgl/stream/buffer_stream.c"
	"src/mgl/string/manipulation.c"
	"src/mgl/string/conversion.c"
	"src/mgl/thread/win32_thread.c"
	"src/mgl/thread/win32_mutex.c"
	"src/mgl/thread/win32_atomic.c"
	"src/mgl/thread/posix_thread.c"
	"src/mgl/thread/posix_mutex.c"
	"src/mgl/thread/posix_atomic.c"
	"src/mgl/container/iterator.c"
	"src/mgl/container/array.c"
	"src/mgl/container/vector.c"
	"src/mgl/container/singly_linked_list.c"
	"src/mgl/container/doubly_linked_list.c"
	"src/mgl/file/archive.c"
	"src/mgl/file/windows_standard_archive.c"
	"src/mgl/input/input_manager.c"
	"src/mgl/input/window.c"
	"src/mgl/input/windows_window.c"
	"src/mgl/input/x_window.c"
	"src/mgl/network/windows_ipv4_address.c"
	"src/mgl/network/windows_network.c"
	"src/mgl/network/windows_tcp_socket.c"
	"src/mgl/network/windows_tcp_listener.c"
)

set(MGL_INCLUDE
	"include/mgl/api_utils.h"
	"include/mgl/entry.h"
	"include/mgl/error.h"
	"include/mgl/type.h"
	"include/mgl/math/scalar.h"
	"include/mgl/math/simd.h"
	"include/mgl/math/vector4.h"
	"include/mgl/math/matrix4x4.h"
	"include/mgl/math/quaternion.h"
	"include/mgl/math/quaternion_matrix4x4.h"
	"include/mgl/math/transform_matrix4x4.h"
	"include/mgl/math/transform_quaternion.h"
	"include/mgl/memory/manipulation.h"
	"include/mgl/memory/crc.h"
	"include/mgl/memory/allocator.h"
	"include/mgl/memory/linear_allocator.h"
	"include/mgl/memory/stack_allocator.h"
	"include/mgl/memory/pool_allocator.h"
	"include/mgl/memory/debug_allocator.h"
	"include/mgl/stream/stream.h"
	"include/mgl/stream/buffer_stream.h"
	"include/mgl/string/manipulation.h"
	"include/mgl/string/conversion.h"
	"include/mgl/thread/thread.h"
	"include/mgl/thread/mutex.h"
	"include/mgl/thread/atomic.h"
	"include/mgl/container/iterator.h"
	"include/mgl/container/array.h"
	"include/mgl/container/vector.h"
	"include/mgl/container/singly_linked_list.h"
	"include/mgl/container/doubly_linked_list.h"
	"include/mgl/file/archive.h"
	"include/mgl/file/windows_standard_archive.h"
	"include/mgl/input/keyboard.h"
	"include/mgl/input/mouse.h"
	"include/mgl/input/axis.h"
	"include/mgl/input/button.h"
	"include/mgl/input/action.h"
	"include/mgl/input/input_manager.h"
	"include/mgl/input/window.h"
	"include/mgl/input/windows_window.h"
	"include/mgl/input/x_window.h"
	"include/mgl/network/network.h"
	"include/mgl/network/ipv4_address.h"
	"include/mgl/network/tcp_socket.h"
	"include/mgl/network/tcp_listener.h"
)

#####################################################
# Set options
option(MGL_BUILD_SHARED OFF)
option(MGL_BUILD_SSE OFF)
option(MGL_MATH_USE_SIMD OFF)

#####################################################
# Create MGL target and set its properties

if(MGL_BUILD_SHARED)
	add_library(mgl SHARED ${MGL_SOURCE} ${MGL_INCLUDE})
	target_compile_definitions(mgl PUBLIC MGL_BUILD_SHARED)
else()
	add_library(mgl STATIC ${MGL_SOURCE} ${MGL_INCLUDE})
endif()
set_property(TARGET mgl PROPERTY C_STANDARD 11)
add_library(MGL::mgl ALIAS mgl)

generate_export_header(mgl)
target_include_directories(mgl
	PUBLIC
		$<INSTALL_INTERFACE:include/>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CMAKE_CURRENT_SOURCE_DIR}/include
)
if(UNIX)
    target_link_libraries(mgl INTERFACE m dl pthread) # Link math lib
    find_package(X11 REQUIRED)
    target_include_directories(mgl PUBLIC ${X11_INCLUDE_DIR})
    target_link_libraries(mgl PUBLIC ${X11_LIBRARIES})
endif()
if(!MSVC)
    target_compile_options(mgl INTERFACE -msse4.1)
endif()

#target_compile_options(mgl PRIVATE -WX -W3)
target_compile_definitions(mgl
	PUBLIC
		MGL_VERSION="${PROJECT_VERSION}"
		MGL_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
		MGL_VERSION_MINOR=${PROJECT_VERSION_MINOR}
		MGL_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PRIVATE
		MGL_API_EXPORT
)

if (MGL_BUILD_SSE)
	target_compile_definitions(mgl PUBLIC MGL_BUILD_SSE)
endif()
if (MGL_MATH_USE_SIMD)
	target_compile_definitions(mgl PUBLIC MGL_MATH_USE_SIMD)
endif()

# Add file filters
foreach(_source IN ITEMS ${MGL_SOURCE} ${MGL_INCLUDE})
	if (IS_ABSOLUTE "${_source}")
		file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
	else()
		set(_source_rel "${_source}")
	endif()
	get_filename_component(_source_path "${_source_rel}" PATH)
	string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
	source_group("${_source_path_msvc}" FILES "${_source}")
endforeach()

#####################################################
# Installation instructions

include (GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/MGL)

install(TARGETS mgl
    EXPORT mgl-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set_target_properties(mgl PROPERTIES EXPORT_NAME MGL)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export targets
install(EXPORT mgl-targets
	FILE
		MGLTargets.cmake
	NAMESPACE
		MGL::
	DESTINATION
		${INSTALL_CONFIGDIR}
)

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MGLConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/MGLConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MGLConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# Install the Config, ConfigVersion and custom find modules
install(FILES
    #${CMAKE_CURRENT_LIST_DIR}/cmake/FindXXX.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MGLConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MGLConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
# Exporting from the build tree

#configure_file(
#	${CMAKE_CURRENT_LIST_DIR}/cmake/FindXXX.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/FindXXX.cmake
#    COPYONLY)

export(EXPORT mgl-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/MGLTargets.cmake NAMESPACE MGL::)

# Register package in user's package registry
export(PACKAGE MGL)

##############################################
# Build tests
option(MGL_BUILD_TESTS OFF)
if(MGL_BUILD_TESTS)
    add_subdirectory(tests/)
endif()

##############################################
# Build examples
option(MGL_BUILD_EXAMPLES ON)
if(MGL_BUILD_EXAMPLES)
    file(GLOB_RECURSE files "src/examples/*.c")
    foreach(file ${files})
	string(REGEX REPLACE "(^.*\\/|\\.[^.]*$)" "" file_without_ext ${file})
	set(file_without_ext example_${file_without_ext})
	add_executable(${file_without_ext} ${file})
	target_link_libraries(${file_without_ext} mgl)
	set_target_properties(${file_without_ext} PROPERTIES FOLDER Examples)
endforeach()
endif()
