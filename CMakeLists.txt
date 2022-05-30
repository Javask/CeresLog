cmake_minimum_required(VERSION 3.18)

project(CeresLog VERSION 1.0.0 LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/CPM.cmake)

option(CERESLOG_BUILD_OWN_PACKAGES "Build all dependencies from scratch." OFF)
if(NOT CERESLOG_BUILD_OWN_PACKAGES)
  set(CPM_USE_LOCAL_PACKAGES ON)
else()
  message(STATUS "Building CeresLog dependencies from scratch...")
  set(CPM_USE_LOCAL_PACKAGES OFF)
endif()


set(CMAKE_CXX_FLAGS_ASAN "-fsanitize=address -fno-omit-frame-pointer -g -Wall")
set(CMAKE_EXE_LINKER_FLAGS_ASAN  "-fsanitize=address -g -Wall")

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

if(MSVC)
  set(CERES_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc")
else()
  set(CERES_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -fPIC)
endif()

if(UNIX)
    add_definitions(-DCERESLOG_PLATFORM_LINUX)
elseif(WIN32)
    add_definitions(-DCERESLOG_PLATFORM_WINDOWS)
    if(MSVC)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
        set(BUILD_SHARED_LIBS TRUE)
    endif()
endif()


CPMAddPackage(NAME Utilities 
              GIT_TAG v1.0.0-alpha6
              GITHUB_REPOSITORY Javask/Utilities
              OPTIONS
                "UTILITIES_BUILD_TESTS OFF")

file(GLOB_RECURSE CERESLOG_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_library(CeresLog SHARED ${CERESLOG_SOURCE_FILES})
set_target_properties(CeresLog PROPERTIES CXX_STANDARD 20 COMPILE_OPTIONS "${CERES_CXX_FLAGS}")
target_link_libraries(CeresLog Utilities::Utilities)
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
  enable_testing()
  add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/test/")
endif()

