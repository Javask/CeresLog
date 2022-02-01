cmake_minimum_required(VERSION 3.7)

project(CeresLog)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCERESLOG_DEBUG)
endif()

if(UNIX)
    add_definitions(-DCERESLOG_PLATFORM_LINUX)
elseif(WIN32)
    add_definitions(-DCERESLOG_PLATFORM_WINDOWS)
endif()

file(GLOB_RECURSE CERESLOG_HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.h"
							   "${CMAKE_CURRENT_LIST_DIR}/src/*.hpp")
file(GLOB_RECURSE CERESLOG_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

set(CeresLog_INDLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")
file(GLOB_RECURSE CERESLOG_INCLUDE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/include/*.h")


add_library(CeresLog STATIC ${CERESLOG_SOURCE_FILES} ${CERESLOG_HEADER_FILES})
target_include_directories(CeresLog INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")
add_library(CeresLog::CeresLog ALIAS CeresLog)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(CERESLOG_BUILD_TESTS_DEFAULT ON)
else()
  message(STATUS "CeresLog running as subproject!")
  set(CERESLOG_BUILD_TESTS_DEFAULT OFF)
endif()
option(CERESLOG_BUILD_TESTS "Build CeresLog Testing Project" ${CERESLOG_BUILD_TESTS_DEFAULT})
if(CERESLOG_BUILD_TESTS)
  message(STATUS "Building CeresLog tests...")
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/thirdparty/catch")
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/")
else()
  message(STATUS "CeresLog-Tests disabled..")
endif()

