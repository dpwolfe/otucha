add_executable (tests main.cpp s1_Matrix3x3_tests.cpp warbler_Console_tests.cpp rffalcon_TextureAtlas_tests.cpp)
target_link_libraries (tests gtest s1 warbler  rffalcon)
set_property(TARGET tests PROPERTY CXX_STANDARD 11)
