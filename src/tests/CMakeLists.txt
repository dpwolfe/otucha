set(CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/rffalcon_AffinePoint_tests.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/rffalcon_AffineVector_tests.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/rffalcon_Matrix3x3_tests.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/rffalcon_Matrix4x4_tests.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/rffalcon_TextureAtlas_tests.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/rffalcon_VertexAttribute_tests.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/warbler_Console_tests.cpp) 

if(COVERALLS)
	set(COVERAGE_SRCS ${RFFALCON_SRCS} ${WARBLER_SRCS} ${TERASCA_SRCS} ${CPP_FILES})
	coveralls_setup("${COVERAGE_SRCS}" ${COVERALLS_UPLOAD} "${PROJECT_SOURCE_DIR}/submodules/coveralls-cmake/cmake" ${COVERALLS_VERBOSE})
endif()

add_executable(otucha_tests ${CPP_FILES})
target_link_libraries (otucha_tests gtest warbler rffalcon GLEW_1110 freetype)

set_property(TARGET otucha_tests PROPERTY CXX_STANDARD 11)
add_test(NAME otucha_tests COMMAND otucha_tests)
