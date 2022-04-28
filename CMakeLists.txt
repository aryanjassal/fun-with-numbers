cmake_minimum_required (VERSION 3.22)
 
project(
  fun_with_numbers
  LANGUAGES CXX
  VERSION 0.2.0.0
  DESCRIPTION "A C++ recreation of the program Fun With Numbers, originally created by Dingle, for my Software Design and Development assignment."
  HOMEPAGE_URL "https://github.com/AryanJassal/FunWithNumbers"
)

set(CODE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

set(CODE_FILES 
  ${CODE_DIR}/main.cpp 
  ${CODE_DIR}/utils.cpp 
  ${CODE_DIR}/ascii.cpp 
  ${CODE_DIR}/tui.cpp
  ${CODE_DIR}/classes.cpp
)
set(INCLUDE_FILES 
  ${INCLUDE_DIR}/utils.hpp 
  ${INCLUDE_DIR}/ascii.hpp 
  ${INCLUDE_DIR}/tui.hpp
  ${INCLUDE_DIR}/classes.hpp
)
set(SOURCES ${INCLUDE_FILES} ${CODE_FILES})

add_executable(fun_with_numbers ${SOURCES})

set_target_properties(fun_with_numbers
  PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 20
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

target_include_directories(fun_with_numbers
  PRIVATE ${INCLUDE_DIR}
)

target_link_options(fun_with_numbers PRIVATE -Ofast -s -static)
