set(TERASCA_SRCS Controller.cpp Controller.hpp
				 GLFWController.cpp GLFWController.hpp
				 ModelView.cpp ModelView.hpp
				 ModelViewWithShader.cpp ModelViewWithShader.hpp
				 ShaderProgram.cpp ShaderProgram.hpp)
add_library(terasca ${TERASCA_SRCS})