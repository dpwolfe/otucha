set(CPP_FILES Controller.cpp GLFWController.cpp ModelView.cpp ModelViewWithShader.cpp ShaderProgram.cpp)
set(HPP_FILES Controller.hpp GLFWController.hpp ModelView.hpp ModelViewWithShader.hpp ShaderProgram.hpp)
add_library(terasca ${CPP_FILES} ${HPP_FILES})
