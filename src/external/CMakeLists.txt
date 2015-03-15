if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
	add_definitions( "/MP" )
endif()

add_definitions(
	-DGL_GLEXT_PROTOTYPES
	-DGLEW_STATIC
	-DGLEW_NO_GLU
	-D_CRT_SECURE_NO_WARNINGS
)

### GLFW ###
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW documentation")

add_subdirectory(glfw-3.0.4)
add_subdirectory(gtest-1.7.0)
add_subdirectory(freetype-2.5.5)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLEW ###

set(GLEW_SOURCE
	glew-1.11.0/src/glew.c
)

set(GLEW_HEADERS
)


add_library(GLEW_1110 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_1110
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)
