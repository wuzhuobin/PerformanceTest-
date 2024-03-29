cmake_minimum_required(VERSION 3.0)
get_filename_component(
  PROJECT_NAME
  ${CMAKE_CURRENT_SOURCE_DIR}
  NAME_WE
)
message(${PROJECT_NAME})
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

option(BUILD_TESTING "Build Test." OFF)
option(BUILD_COVERAGE "Build Test Coverage report." OFF)
option(BUILD_DOC "Build Documentation." OFF)
option(BUILD_SHARED_LIBS "Build shared libraries." OFF)
option(BUILD_EXAMPLE "Build Example." OFF)
option(SUPER_BUILD "Super build dependecies." OFF)
option(BUILD_FACADE "Build Message System Facade" OFF)
set(BUILD_SHARED_LIBS ON)

if(SUPER_BUILD)
  add_subdirectory(superbuild)
  return()
elseif(NOT EXTERNAL_SUPERBUILD_DIR)
  set(EXTERNAL_SUPERBUILD_DIR "" CACHE PATH "External superbuild dir.")
else()

endif()
if(BUILD_COVERAGE)
  include(test/coverage.cmake)
  append_coverage_compiler_flags()
endif()
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
if(BUILD_EXAMPLE)
  add_subdirectory(example)
endif()
if(BUILD_DOC)
  add_subdirectory(doc)
endif()

if(DEFINED ENV{OE_CMAKE_TOOLCHAIN_FILE})
  include(toolchain.cmake)
endif()

add_subdirectory(src/PerformanceTest)