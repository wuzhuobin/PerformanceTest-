cmake_minimum_required(VERSION 3.0)
get_filename_component(
  PROJECT_NAME
  ${CMAKE_CURRENT_SOURCE_DIR}
  NAME_WE
)

project(${PROJECT_NAME})
message(${PROJECT_NAME})

find_package(Qt5Test REQUIRED)
set(CMAKE_AUTOMOC ON)

enable_testing()

file(
  GLOB
  TEST_CPP
  *[Test|Benchmark].c*
)

foreach(TEST_CPP_ IN LISTS TEST_CPP)
  get_filename_component(
    TARGET_NAME
    ${TEST_CPP_}
    NAME_WE
  )

  add_executable(
    ${TARGET_NAME}
    ${TEST_CPP_}
  )

  target_link_libraries(
    ${TARGET_NAME}
    PUBLIC
    Qt5::Test 
    PerformanceTest
  )

  add_test(
    NAME
    ${TARGET_NAME}
    COMMAND
    ${TARGET_NAME}
  )

#   set_tests_properties(
#     ${TARGET_NAME}
#     PROPERTIES
#     ENVIRONMENT
#     "LD_LIBRARY_PATH=${fastcdr_LIB_DIR};QT_QPA_PLATFORM=offscreen"
#   )
endforeach()