set(CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/GLFWController.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/ModelView.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/ModelViewWithShader.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/ShaderProgram.cpp)
set(HPP_FILES Controller.hpp GLFWController.hpp ModelView.hpp ModelViewWithShader.hpp ShaderProgram.hpp)
add_library(terasca ${CPP_FILES} ${HPP_FILES})
