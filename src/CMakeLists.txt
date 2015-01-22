cmake_minimum_required (VERSION 2.6)
project (otucha)
find_package(OpenGL REQUIRED)
# The version number
set (otucha_VERSION_MAJOR 0)
set (otucha_VERSION_MINOR 1)

option(OTUCHA_EMSCRIPTEN_ENABLED "Enable building with Emscripten" ON)
if(OTUCHA_EMSCRIPTEN_ENABLED)
	message(STATUS "Enabling Emscripten compile")

	# Attempt to get Emscripten location
	if ("${EMSCRIPTEN_ROOT_PATH}" STREQUAL "")
		set(EMSCRIPTEN_ROOT_PATH "$ENV{EMSCRIPTEN}")
	endif()

	# Fail if Emscripten not found
	if ("${EMSCRIPTEN_ROOT_PATH}" STREQUAL "")
		message(FATAL_ERROR "Could not locate Emscripten compiler.  Either set the EMSCRIPTEN environment variable, or pass -DEMSCRIPTEN_ROOT_PATH=xxx to CMake to specify the location.")
	endif()

	# Check Emscripten version
	set(EMSCRIPTEN_REQUIRED_VERSION 1.25.0)
	if(EXISTS "${EMSCRIPTEN_ROOT_PATH}/emscripten-version.txt")
		file(READ "${EMSCRIPTEN_ROOT_PATH}/emscripten-version.txt" EMSCRIPTEN_VERSION)
		# string replace only to clean up console output, not otherwise required
		string(REPLACE "\n" "" EMSCRIPTEN_VERSION "${EMSCRIPTEN_VERSION}")
		message(STATUS "Found Emscripten ${EMSCRIPTEN_VERSION} at ${EMSCRIPTEN_ROOT_PATH}")
		if(EMSCRIPTEN_VERSION VERSION_LESS ${EMSCRIPTEN_REQUIRED_VERSION})
			message(FATAL_ERROR "Emscripten version >= ${EMSCRIPTEN_REQUIRED_VERSION} is required.")
		endif()
	endif()
	
	# Emscripten compiler options
	set(CMAKE_C_COMPILER "${EMSCRIPTEN_ROOT_PATH}/emcc")
	set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_ROOT_PATH}/em++")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-warn-absolute-paths -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1 --memory-init-file 0")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-warn-absolute-paths -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1 --memory-init-file 0")
	
	# Emscripten toolchain options
	set(EMSCRIPTEN_TOOLCHAIN_OPTIONS
		-DCMAKE_MODULE_PATH:PATH=${EMSCRIPTEN_ROOT_PATH}/cmake/Modules
		-DCMAKE_TOOLCHAIN_FILE:FILEPATH=${EMSCRIPTEN_ROOT_PATH}/cmake/Modules/Platform/Emscripten.cmake
		-DCMAKE_CXX_COMPILER:FILEPATH=${CMAKE_CXX_COMPILER}
		-DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
		-DCMAKE_C_COMPILER:FILEPATH=${CMAKE_C_COMPILER}
		-DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
		-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE})
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