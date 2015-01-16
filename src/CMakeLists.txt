cmake_minimum_required (VERSION 2.6)
project (otucha)
find_package(OpenGL REQUIRED)
# The version number
set (otucha_VERSION_MAJOR 0)
set (otucha_VERSION_MINOR 1)

# Attempt to get Emscripten location
if ("${EMSCRIPTEN_ROOT_PATH}" STREQUAL "")
	set(EMSCRIPTEN_ROOT_PATH "$ENV{EMSCRIPTEN}")
endif()

# Fail if Emscripten not found
if ("${EMSCRIPTEN_ROOT_PATH}" STREQUAL "")
	message(FATAL_ERROR "Could not locate Emscripten compiler.  Either set the EMSCRIPTEN environment variable, or pass -DEMSCRIPTEN_ROOT_PATH=xxx to CMake to specify the location.")
endif()

# Check Emscripten version
set(EMSCRIPTEN_REQUIRED_VERSION 1.26.0)
if(EXISTS "${EMSCRIPTEN_ROOT_PATH}/emscripten-version.txt")
	file(READ "${EMSCRIPTEN_ROOT_PATH}/emscripten-version.txt" EMSCRIPTEN_VERSION)
	# string replace only to clean up console output, not otherwise required
	string(REPLACE "\n" "" EMSCRIPTEN_VERSION "${EMSCRIPTEN_VERSION}")
	message(STATUS "Found Emscripten ${EMSCRIPTEN_VERSION}")
	if(EMSCRIPTEN_VERSION VERSION_LESS ${EMSCRIPTEN_REQUIRED_VERSION})
		message(FATAL_ERROR "Emscripten version >= ${EMSCRIPTEN_REQUIRED_VERSION} is required.")
	endif()
endif()

# Header to pass some of the CMake settings to the source code
configure_file (
	"${PROJECT_SOURCE_DIR}/otuchaConfig.h.in"
	"${PROJECT_BINARY_DIR}/otuchaConfig.h"
)

add_definitions(
	-DGL_GLEXT_PROTOTYPES
	-DGLEW_STATIC
	-DGLEW_NO_GLU
	-D_CRT_SECURE_NO_WARNINGS
)

include_directories (
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/rffalcon"
	"${PROJECT_SOURCE_DIR}/s1"
	"${PROJECT_SOURCE_DIR}/terasca"
	"${PROJECT_SOURCE_DIR}/external/glfw-3.0.4/include"
	"${PROJECT_SOURCE_DIR}/external/glew-1.11.0/include"
)

add_subdirectory (rffalcon)
add_subdirectory (s1)
add_subdirectory (terasca)

# Compile external dependencies
add_subdirectory (external)

add_executable (otucha otucha.cpp)
target_link_libraries (otucha rffalcon s1 terasca ${OPENGL_LIBRARY} glfw GLEW_1110)