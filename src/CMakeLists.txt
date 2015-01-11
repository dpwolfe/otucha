cmake_minimum_required (VERSION 2.6)
project (otucha)
# The version number
set (otucha_VERSION_MAJOR 0)
set (otucha_VERSION_MINOR 1)

# Header to pass some of the CMake settings to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/otuchaConfig.h.in"
	"${PROJECT_BINARY_DIR}/otuchaConfig.h"
	)

include_directories ("${PROJECT_BINARY_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/rffalcon")
include_directories ("${PROJECT_SOURCE_DIR}/s1")
include_directories ("${PROJECT_SOURCE_DIR}/terasca")
add_subdirectory (rffalcon)
add_subdirectory (s1)
add_subdirectory (terasca)

add_executable (otucha otucha.cpp)
target_link_libraries (otucha rffalcon s1 terasca)