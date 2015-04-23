set(CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/rffalcon_Matrix3x3_tests.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/warbler_Console_tests.cpp
              ${CMAKE_CURRENT_SOURCE_DIR}/rffalcon_TextureAtlas_tests.cpp) 

if(COVERALLS)
	set(COVERAGE_SRCS ${RFFALCON_SRCS} ${WARBLER_SRCS} ${TERASCA_SRCS})
	coveralls_setup("${COVERAGE_SRCS}" ${COVERALLS_UPLOAD} "${PROJECT_SOURCE_DIR}/external/coveralls-cmake")
endif()

add_executable(tests ${CPP_FILES})

set_property(TARGET tests PROPERTY CXX_STANDARD 11)

add_test(all "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests")
