include(CTest)
include("${CMAKE_CURRENT_LIST_DIR}/../thirdparty/catch/contrib/Catch.cmake")
enable_testing()

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.h"
							   "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
set(TEST_PROJECT_NAME "${PROJECT_NAME}_Test")

add_executable(${TEST_PROJECT_NAME} ${TEST_FILES})
target_link_libraries(${TEST_PROJECT_NAME} Catch2::Catch2 ${PROJECT_NAME})
add_dependencies(${TEST_PROJECT_NAME} Catch2::Catch2 ${PROJECT_NAME})

catch_discover_tests(${TEST_PROJECT_NAME})