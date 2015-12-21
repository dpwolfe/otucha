set(CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../AffinePoint.cpp 
              ${CMAKE_CURRENT_SOURCE_DIR}/../AffineVector.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../Block.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../Matrix3x3.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../Matrix4x4.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../ModelBase.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../PhongMaterial.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../TextureAtlas.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../TextureFont.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../VertexBuffer.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../VertexAttribute.cpp)
set(HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../vec.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../AffinePoint.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../AffineVector.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../Block.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../Matrix3x3.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../Matrix4x4.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../ModelBase.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../PhongMaterial.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../TextureAtlas.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../TextureFont.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../VertexBuffer.hpp
              ${CMAKE_CURRENT_SOURCE_DIR}/../VertexAttribute.hpp)

add_definitions(
    -DTEST
)

add_library(rffalcon_test ${CPP_FILES} ${HPP_FILES})
