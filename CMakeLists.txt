cmake_minimum_required(VERSION 3.18)

project(CeresLog VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_ASAN "-fsanitize=address -fno-omit-frame-pointer -g -Wall")
set(CMAKE_EXE_LINKER_FLAGS_ASAN  "-fsanitize=address -g -Wall")

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

if(UNIX)
    add_definitions(-DCERESLOG_PLATFORM_LINUX)
elseif(WIN32)
    add_definitions(-DCERESLOG_PLATFORM_WINDOWS)
    if(MSVC)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
        set(BUILD_SHARED_LIBS TRUE)
    endif()
endif()

file(GLOB_RECURSE CERESLOG_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_library(CeresLog SHARED ${CERESLOG_SOURCE_FILES})
set_target_properties(CeresLog PROPERTIES CXX_STANDARD 20)

target_include_directories(CeresLog
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(CeresLog::CeresLog ALIAS CeresLog)

option(CERESLOG_BUILD_TESTS "Build CeresLog Tests" ON)
if(CERESLOG_BUILD_TESTS)
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/")
endif()

