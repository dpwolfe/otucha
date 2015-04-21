add_executable (tests main.cpp rffalcon_Matrix3x3_tests.cpp warbler_Console_tests.cpp rffalcon_TextureAtlas_tests.cpp)
target_link_libraries (tests gtest warbler rffalcon GLEW_1110 freetype)
set_property(TARGET tests PROPERTY CXX_STANDARD 11)

if (COVERALLS)
	set(COVERAGE_SRCS "${PROJECT_SOURCE_DIR}/rffalcon/Matrix3x3.cpp" "${PROJECT_SOURCE_DIR}/rffalcon/TextureAtlas.cpp"
		"${PROJECT_SOURCE_DIR}/warbler/Console.cpp")
	coveralls_setup(${COVERAGE_SRCS} ON)
endif()