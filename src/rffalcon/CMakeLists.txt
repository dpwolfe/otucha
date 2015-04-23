set(CPP_FILES AffinePoint.cpp AffineVector.cpp Block.cpp Matrix3x3.cpp Matrix4x4.cpp ModelBase.cpp
              PhongMaterial.cpp TextureAtlas.cpp TextureFont.cpp VertexBuffer.cpp VertexAttribute.cpp)
set(HPP_FILES vec.hpp AffinePoint.hpp AffineVector.hpp Block.hpp Matrix3x3.hpp Matrix4x4.hpp ModelBase.hpp
              PhongMaterial.hpp TextureAtlas.hpp TextureFont.hpp VertexBuffer.hpp VertexAttribute.hpp)
add_library(rffalcon ${CPP_FILES} ${HPP_FILES})
