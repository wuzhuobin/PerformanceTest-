cmake_minimum_required(VERSION 3.0)
get_filename_component(
  PROJECT_NAME
  ${CMAKE_CURRENT_SOURCE_DIR}
  NAME_WE
)
project(${PROJECT_NAME})
message(${PROJECT_NAME})

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
# find_package(Qt5Charts REQUIRED)
find_library(QWT_LIBRARY "qwt")
find_path(QWT_INCLUDE_DIR "qwt.h")
if(${QWT_LIBRARY} OR ${QWT_INCLUDE_DIR})
  message(FATAL_ERROR "Cannot find QWT_LIBRARY OR QWT_INCLUDE_DIR")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(
  GLOB
  PROJECT_SRC
  ${PROJECT_SOURCE_DIR}/*.c*
)

file(
  GLOB
  PROJECT_INC
  ${PROJECT_SOURCE_DIR}/*.h*
)

file(
  GLOB
  PROJECT_UI
  ${PROJECT_SOURCE_DIR}/*.ui
)

file(
  GLOB
  PROJECT_QRC
  ${PROJECT_SOURCE_DIR}/*.qrc
)

add_library(
  ${PROJECT_NAME}
  ${PROJECT_SRC}
  ${PROJECT_INC}
  ${PROJECT_UI}
  ${PROJECT_QRC}
)

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_BINARY_DIR}
  ${QWT_INCLUDE_DIR}
)

target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC
  Qt5::Core
  Qt5::Widgets
  Qt5::OpenGL
#   Qt5::Charts
  ${QWT_LIBRARY}
)

add_executable(
  ${PROJECT_NAME}_main
  ${PROJECT_SOURCE_DIR}/main/main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}_main
  PUBLIC
  ${PROJECT_NAME}
)