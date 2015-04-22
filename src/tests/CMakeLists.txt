if (COVERALLS)
	set(COVERAGE_SRCS ${RFFALCON_SRCS} ${WARBLER_SRCS} ${TERASCA_SRCS})
	coveralls_setup("${COVERAGE_SRCS}" ${COVERALLS_UPLOAD} "${PROJECT_SOURCE_DIR}/external/coveralls-cmake")
endif()

enable_testing()

add_executable(tests main.cpp rffalcon_Matrix3x3_tests.cpp warbler_Console_tests.cpp rffalcon_TextureAtlas_tests.cpp)
target_link_libraries (tests gtest warbler rffalcon GLEW_1110 freetype)
set_property(TARGET tests PROPERTY CXX_STANDARD 11)

add_test(all "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests")