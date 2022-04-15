cmake_minimum_required (VERSION 3.23)
 
project(
  fun_with_numbers
  LANGUAGES CXX
  VERSION 0.2.0.0
  DESCRIPTION "A C++ recreation of the program Fun With Numbers, originally created by Dingle, for my Software Design and Development assignment."
  HOMEPAGE_URL "https://github.com/AryanJassal/FunWithNumbers"
)

set(CODE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCES ${CODE_DIR}/main.cpp ${INCLUDE_DIR}/oof.h)

add_executable(fun_with_numbers ${SOURCES})
# target_include_directories(fun_with_numbers PRIVATE ${CODE_DIR})

set_target_properties(fun_with_numbers
  PROPERTIES
    CXX_EXTENSIONS OFF
    CXX_STANDARD 20
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

target_include_directories(fun_with_numbers
  PRIVATE "${CMAKE_SOURCE_DIR}/include"
)

# target_link_libraries(fun_with_numbers)
