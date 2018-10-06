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
)

set(MGL_INCLUDE
	"include/mgl/api_utils.h"
	"include/mgl/entry.h"
	"include/mgl/error.h"
	"include/mgl/type.h"
	"include/mgl/math/vector.h"
)

#####################################################
# Set options
option(MGL_BUILD_SHARED OFF)

#####################################################
# Create MGL target and set its properties


if(MGL_BUILD_SHARED)
	add_library(mgl SHARED ${MGL_SOURCE} ${MGL_INCLUDE})
	target_compile_definitions(mgl PUBLIC MGL_BUILD_SHARED)
else()
	add_library(mgl STATIC ${MGL_SOURCE} ${MGL_INCLUDE})
endif()
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
target_compile_options(mgl PRIVATE -WX -W3)
target_compile_definitions(mgl
	PUBLIC
		MGL_VERSION="${PROJECT_VERSION}"
		MGL_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
		MGL_VERSION_MINOR=${PROJECT_VERSION_MINOR}
		MGL_VERSION_PATCH=${PROJECT_VERSION_PATCH}
	PRIVATE
		MGL_API_EXPORT
)

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
add_subdirectory(tests/)