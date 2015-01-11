cmake_minimum_required (VERSION 2.6)
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
target_link_libraries (otucha rffalcon s1 terasca ${OPENGL_LIBRARY} ${GLFW_LIBRARIES} GLEW_1110)