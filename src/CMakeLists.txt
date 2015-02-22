cmake_minimum_required (VERSION 2.6)

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
	set(CMAKE_C_COMPILER "${EMSCRIPTEN_ROOT_PATH}/emcc.bat")
	set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_ROOT_PATH}/em++.bat")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-warn-absolute-paths -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1 -s USE_GLFW=3 --embed-file ${PROJECT_SOURCE_DIR}/simple.vsh --embed-file ${PROJECT_SOURCE_DIR}/simple.fsh --memory-init-file 0")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-warn-absolute-paths -s ALLOW_MEMORY_GROWTH=1 -s ASSERTIONS=1 -s USE_GLFW=3 --embed-file ${PROJECT_SOURCE_DIR}/simple.vsh --embed-file ${PROJECT_SOURCE_DIR}/simple.fsh --memory-init-file 0")
	set(CMAKE_MODULE_PATH "${EMSCRIPTEN_ROOT_PATH}/cmake/Modules")
	set(CMAKE_TOOLCHAIN_FILE "${EMSCRIPTEN_ROOT_PATH}/cmake/Modules/Platform/Emscripten.cmake")
	set(CMAKE_EXE_LINKER_FLAGS "-o otucha.html ${CMAKE_EXE_LINKER_FLAGS}")
else()
	include_directories (
		"${PROJECT_SOURCE_DIR}/external/glfw-3.0.4/include"
		"${PROJECT_SOURCE_DIR}/external/glew-1.11.0/include"
	)
	
	# Copy of shader files
	file(GLOB shaderFiles "${PROJECT_SOURCE_DIR}/*.*sh")
	
	foreach(file ${shaderFiles})
		execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${file} ${PROJECT_BINARY_DIR})
	endforeach()
endif()

project (otucha)
find_package(OpenGL REQUIRED)
# The version number
set (otucha_VERSION_MAJOR 0)
set (otucha_VERSION_MINOR 1)

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
)

add_subdirectory (rffalcon)
add_subdirectory (s1)
add_subdirectory (terasca)

if(NOT OTUCHA_EMSCRIPTEN_ENABLED)
	# Compile external dependencies
	add_subdirectory (external)
endif()

add_executable (otucha otucha.cpp)
if(OTUCHA_EMSCRIPTEN_ENABLED)
	target_link_libraries (otucha rffalcon s1 terasca ${OPENGL_LIBRARY})
else()
	target_link_libraries (otucha rffalcon s1 terasca ${OPENGL_LIBRARY} glfw GLEW_1110)
endif()