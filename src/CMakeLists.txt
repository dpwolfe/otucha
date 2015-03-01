cmake_minimum_required (VERSION 2.6)
project (otucha)
find_package(OpenGL REQUIRED)
# The version number
set (otucha_VERSION_MAJOR 0)
set (otucha_VERSION_MINOR 1)

option(OTUCHA_EMSCRIPTEN_ENABLED "Enable building with Emscripten" ON)
option(OTUCHA_DO_NOT_WARN_GL_H "Turn off the warning for gl.h and gl3.h both begin defined on Mac" OFF)

if(OTUCHA_EMSCRIPTEN_ENABLED)
	message(STATUS "Enabling Emscripten compile")

	# Attempt to get Emscripten location
	if("${EMSCRIPTEN_ROOT_PATH}" STREQUAL "")
		set(EMSCRIPTEN_ROOT_PATH "$ENV{EMSCRIPTEN}")
	endif()

	# Fail if Emscripten not found
	if("${EMSCRIPTEN_ROOT_PATH}" STREQUAL "")
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
	if(WIN32)
		set(CMAKE_C_COMPILER "${EMSCRIPTEN_ROOT_PATH}/emcc.bat")
		set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_ROOT_PATH}/em++.bat")
	else()
		set(CMAKE_C_COMPILER "${EMSCRIPTEN_ROOT_PATH}/emcc")
		set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_ROOT_PATH}/em++")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-warn-absolute-paths -s ALLOW_MEMORY_GROWTH=0 -s ASSERTIONS=1 -s USE_GLFW=3 --embed-file simple.vsh --embed-file simple.fsh --memory-init-file 0")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-warn-absolute-paths -s ALLOW_MEMORY_GROWTH=0 -s ASSERTIONS=1 -s USE_GLFW=3 --embed-file simple.vsh --embed-file simple.fsh --memory-init-file 0")
	set(CMAKE_MODULE_PATH "${EMSCRIPTEN_ROOT_PATH}/cmake/Modules")
	set(CMAKE_TOOLCHAIN_FILE "${EMSCRIPTEN_ROOT_PATH}/cmake/Modules/Platform/Emscripten.cmake")
	set(CMAKE_EXE_LINKER_FLAGS "-o otucha.html ${CMAKE_EXE_LINKER_FLAGS}")
	set(OTUCHA_SHADER_COPY_BUILD_STAGE "PRE_BUILD")
else()
	include_directories (
		"${PROJECT_SOURCE_DIR}/external/glfw-3.0.4/include"
		"${PROJECT_SOURCE_DIR}/external/glew-1.11.0/include"
	)
	if(OTUCHA_DO_NOT_WARN_GL_H)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED")
	endif()
	set(OTUCHA_SHADER_COPY_BUILD_STAGE "POST_BUILD")
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
)

add_subdirectory (rffalcon)
add_subdirectory (s1)
add_subdirectory (terasca)

if(NOT OTUCHA_EMSCRIPTEN_ENABLED)
	# Compile external dependencies
	add_subdirectory (external)
        include_directories(
		"${PROJECT_SOURCE_DIR}/external/include"
		"${gtest_SOURCE_DIR}/include"
	)
	add_subdirectory (tests)
endif()

add_executable (otucha otucha.cpp)
if(OTUCHA_EMSCRIPTEN_ENABLED)
	target_link_libraries (otucha rffalcon s1 terasca ${OPENGL_LIBRARY})
else()
	target_link_libraries (otucha rffalcon s1 terasca ${OPENGL_LIBRARY} glfw GLEW_1110)
endif()

# Copy shader files during pre-build
file(GLOB shaderFiles "${PROJECT_SOURCE_DIR}/*.*sh")
foreach(file ${shaderFiles})
	add_custom_command(TARGET otucha ${OTUCHA_SHADER_COPY_BUILD_STAGE}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${file}
                ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}
                COMMENT "Copying ${file} to ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}")
endforeach()

