cmake_minimum_required(VERSION 3.18)

project(CeresLogTests)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/CPM.cmake)

#add Catch2
CPMAddPackage("gh:catchorg/Catch2@2.13.8")

file(GLOB_RECURSE CERESLOG_TEST_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.h"
							   "${CMAKE_CURRENT_LIST_DIR}/*.cpp")


add_executable(CeresLogTests ${CERESLOG_TEST_FILES})
target_link_libraries(CeresLogTests Catch2::Catch2 CeresLog::CeresLog)
add_dependencies(CeresLogTests Catch2::Catch2 CeresLog::CeresLog)
set_target_properties(CeresLogTests PROPERTIES CXX_STANDARD 20 COMPILE_OPTIONS "${CERES_CXX_FLAGS}")


enable_testing()
add_test(CeresLogTests CeresLogTests)