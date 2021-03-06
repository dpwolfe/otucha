cmake_minimum_required(VERSION 2.8.7)
project(otucha CXX C)
find_package(OpenGL REQUIRED)
find_package(Threads)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/submodules/coveralls-cmake/cmake)

# The version number
set(otucha_VERSION_MAJOR 0)
set(otucha_VERSION_MINOR 1)

option(OTUCHA_EMSCRIPTEN_ENABLED "Enable building with Emscripten" OFF)
option(OTUCHA_EMSCRIPTEN_DEBUG "Enable compile flags for easier JavaScript debugging" OFF)
option(OTUCHA_DO_NOT_WARN_GL_H "Turn off the warning for gl.h and gl3.h both being defined on Mac" OFF)
option(COVERALLS "Turn on Coveralls support" OFF)
option(COVERALLS_UPLOAD "Upload the generated Coveralls json" ON)
option(COVERALLS_VERBOSE "Print verbose statements in Coveralls output" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

if(COVERALLS)
	include(Coveralls)
	coveralls_turn_on_coverage()
endif()

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
	set(EMSCRIPTEN_REQUIRED_VERSION 1.35.0)
	if(EXISTS "${EMSCRIPTEN_ROOT_PATH}/emscripten-version.txt")
		file(READ "${EMSCRIPTEN_ROOT_PATH}/emscripten-version.txt" EMSCRIPTEN_VERSION)
		# string replace only to clean up console output, not otherwise required
		string(REPLACE "\n" "" EMSCRIPTEN_VERSION "${EMSCRIPTEN_VERSION}")
		string(REPLACE "\"" "" EMSCRIPTEN_VERSION "${EMSCRIPTEN_VERSION}")
		message(STATUS "Found Emscripten ${EMSCRIPTEN_VERSION} at ${EMSCRIPTEN_ROOT_PATH}")
		if(EMSCRIPTEN_VERSION VERSION_LESS ${EMSCRIPTEN_REQUIRED_VERSION})
			message(FATAL_ERROR "Emscripten version >= ${EMSCRIPTEN_REQUIRED_VERSION} is required.")
		endif()
	endif()

	# Emscripten compiler options
	if("$ENV{OS}" STREQUAL Windows_NT)
		message(STATUS "Using Emscripten bat files")
		set(CMAKE_C_COMPILER "${EMSCRIPTEN_ROOT_PATH}/emcc.bat")
		set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_ROOT_PATH}/em++.bat")
	else()
		set(CMAKE_C_COMPILER "${EMSCRIPTEN_ROOT_PATH}/emcc")
		set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_ROOT_PATH}/em++")
	endif()
	
	if(OTUCHA_EMSCRIPTEN_DEBUG)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g3 -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g3 -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Oz")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -Oz")
	endif()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror -s ALLOW_MEMORY_GROWTH=0 -s USE_GLFW=3 --embed-file simple.vsh --embed-file simple.fsh --embed-file v3f-t2f-c4f.vsh --embed-file v3f-t2f-c4f.fsh --embed-file DejaVuSansMono.ttf --memory-init-file 0")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -s ALLOW_MEMORY_GROWTH=0 -s USE_GLFW=3 --embed-file simple.vsh --embed-file simple.fsh --embed-file v3f-t2f-c4f.vsh --embed-file v3f-t2f-c4f.fsh --embed-file DejaVuSansMono.ttf --memory-init-file 0")
	set(CMAKE_MODULE_PATH "${EMSCRIPTEN_ROOT_PATH}/cmake/Modules")
	set(CMAKE_TOOLCHAIN_FILE "${EMSCRIPTEN_ROOT_PATH}/cmake/Modules/Platform/Emscripten.cmake")
	set(CMAKE_EXE_LINKER_FLAGS "-o otucha.html ${CMAKE_EXE_LINKER_FLAGS}")
	set(OTUCHA_RESOURCE_COPY_BUILD_STAGE "PRE_BUILD")
else()
	include_directories(
		"${PROJECT_SOURCE_DIR}/submodules/glfw/include"
		"${PROJECT_SOURCE_DIR}/submodules/glew-cmake/include"
	)
	if(OTUCHA_DO_NOT_WARN_GL_H)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED")
	endif()
	if(NOT MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
		set(CMAKE_STANDARD_LIBRARIES ${CMAKE_STANDARD_LIBRARIES})
	endif()
	if("$ENV{CXX}" MATCHES "^.*clang\\+\\+.*$")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	endif()
	set(OTUCHA_SHADER_COPY_BUILD_STAGE "POST_BUILD")
endif()

# Header to pass some of the CMake settings to the source code
configure_file(
	"${PROJECT_SOURCE_DIR}/src/otuchaConfig.h.in"
	"${PROJECT_BINARY_DIR}/src/otuchaConfig.h"
)

add_definitions(
	-DGL_GLEXT_PROTOTYPES
	-DGLEW_STATIC
	-DGLEW_NO_GLU
	-D_CRT_SECURE_NO_WARNINGS
)

include_directories(
	"${PROJECT_BINARY_DIR}/src"
	"${PROJECT_SOURCE_DIR}/src/rffalcon"
	"${PROJECT_SOURCE_DIR}/src/terasca"
	"${PROJECT_SOURCE_DIR}/src/warbler"
	"${PROJECT_SOURCE_DIR}/submodules/freetype2/include"
)

# add internal lib source files
add_subdirectory("${PROJECT_SOURCE_DIR}/src/rffalcon")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/terasca")
add_subdirectory("${PROJECT_SOURCE_DIR}/src/warbler")

# bring list of lib source files to outer scope for test to reference for Coveralls
get_directory_property(RFFALCON_SRCS DIRECTORY "${PROJECT_SOURCE_DIR}/src/rffalcon" DEFINITION CPP_FILES)
get_directory_property(TERASCA_SRCS DIRECTORY "${PROJECT_SOURCE_DIR}/src/terasca" DEFINITION CPP_FILES)
get_directory_property(WARBLER_SRCS DIRECTORY "${PROJECT_SOURCE_DIR}/src/warbler" DEFINITION CPP_FILES)

if(OTUCHA_EMSCRIPTEN_ENABLED)
	# GLFW and GLEW are provided by Emscripten
	add_subdirectory("${PROJECT_SOURCE_DIR}/submodules/freetype2")
else()
	if(MSVC)
		add_definitions( "/MP" )
	else()
		set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries (DLLs).")
	endif()
	
	### GLFW ###
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
	set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
	set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
	set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
	set(GLFW_INSTALL OFF CACHE BOOL "Generate GLFW installation target")
	set(BUILD_TESTING OFF CACHE BOOL "Build testing targets")
	add_subdirectory("${PROJECT_SOURCE_DIR}/submodules/glfw")
	get_directory_property(GLFW_LIBRARIES DIRECTORY "${PROJECT_SOURCE_DIR}/submodules/glfw" DEFINITION glfw_LIBRARIES)
	
	### GLEW ###
	set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "Build the shared glew library") # only build static
	add_subdirectory("${PROJECT_SOURCE_DIR}/submodules/glew-cmake")
	if(MSVC)
		set_target_properties(libglew_static PROPERTIES STATIC_LIBRARY_FLAGS "/machine:x86")
	endif()
	
	add_subdirectory("${PROJECT_SOURCE_DIR}/submodules/freetype2")

	include(CTest)
	enable_testing()
	
	### GOOGLE MOCK ###
	if(MSVC)
		# /MD for gtest
		set(gtest_force_shared_crt ON CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib.")
	endif()
	add_subdirectory("${PROJECT_SOURCE_DIR}/submodules/gmock")
	include_directories(
		"${gtest_SOURCE_DIR}/include"
		"${gmock_SOURCE_DIR}/include"
	)
	
	add_subdirectory("${PROJECT_SOURCE_DIR}/src/tests")
endif()

add_executable(otucha "${PROJECT_SOURCE_DIR}/src/otucha.cpp"
					  "${PROJECT_SOURCE_DIR}/src/DependencyContainer.cpp"
					  "${PROJECT_SOURCE_DIR}/src/DependencyContainer.hpp")
if(OTUCHA_EMSCRIPTEN_ENABLED)
	target_link_libraries(otucha rffalcon terasca warbler ${OPENGL_LIBRARY} freetype)
else()
	target_link_libraries(otucha rffalcon terasca warbler ${OPENGL_LIBRARY} glfw ${GLFW_LIBRARIES} libglew_static freetype)
endif()
set_property(TARGET otucha PROPERTY CXX_STANDARD 11)

# Copy shader files during build
file(GLOB shaderFiles "${PROJECT_SOURCE_DIR}/src/*.*sh")
foreach(file ${shaderFiles})
	add_custom_command(TARGET otucha ${OTUCHA_RESOURCE_COPY_BUILD_STAGE}
		COMMAND ${CMAKE_COMMAND} -E copy_if_different "${file}"
				"${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
				COMMENT "Copying ${file} to ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}")
endforeach()

# Copy font file during build
add_custom_command(TARGET otucha ${OTUCHA_RESOURCE_COPY_BUILD_STAGE}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/submodules/dejavu-fonts-release-latest/dejavu-fonts-ttf/ttf/DejaVuSansMono.ttf"
			${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}
			COMMENT "Copying ${PROJECT_SOURCE_DIR}/submodules/dejavu-fonts-release-latest/dejavu-fonts-ttf/ttf/DejaVuSansMono.ttf to ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}")
