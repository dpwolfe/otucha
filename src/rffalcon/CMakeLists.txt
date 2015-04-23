set(CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/AffinePoint.cpp 
              ${CMAKE_CURRENT_SOURCE_DIR}/AffineVector.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/Block.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/Matrix3x3.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/Matrix4x4.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/ModelBase.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/PhongMaterial.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/TextureAtlas.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/TextureFont.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/VertexBuffer.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/VertexAttribute.cpp)
set(HPP_FILES vec.hpp AffinePoint.hpp AffineVector.hpp Block.hpp Matrix3x3.hpp Matrix4x4.hpp ModelBase.hpp
              PhongMaterial.hpp TextureAtlas.hpp TextureFont.hpp VertexBuffer.hpp VertexAttribute.hpp)
add_library(rffalcon ${CPP_FILES} ${HPP_FILES})
