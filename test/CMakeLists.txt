cmake_minimum_required(VERSION 3.18)

project(CeresLogTests)

#add Catch2
CPMAddPackage("gh:catchorg/Catch2@3.0.1")

file(GLOB_RECURSE CERESLOG_TEST_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.h"
							   "${CMAKE_CURRENT_LIST_DIR}/*.cpp")


add_executable(CeresLogTests ${CERESLOG_TEST_FILES})
target_link_libraries(CeresLogTests $<TARGET_NAME_IF_EXISTS:Catch2::Catch2WithMain> CeresLog::CeresLog)
add_dependencies(CeresLogTests CeresLog::CeresLog)
set_target_properties(CeresLogTests PROPERTIES CXX_STANDARD 20 COMPILE_OPTIONS "${CERES_CXX_FLAGS}")


add_test(CeresLogTests ${EXECUTABLE_OUTPUT_PATH}/CeresLogTests)