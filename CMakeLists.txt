cmake_minimum_required (VERSION 3.11)
 
# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v2.0.0
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
 
# ------------------------------------------------------------------------------
 
project(
  fun_with_numbers
  LANGUAGES CXX
  VERSION 0.2.0.0
  DESCRIPTION "A C++ recreation of the program Fun With Numbers, originally created by Dingle, for my Software Design and Development assignment."
  HOMEPAGE_URL "https://github.com/AryanJassal/FunWithNumbers"
)
 
add_executable(fun_with_numbers src/main.cpp)
target_include_directories(fun_with_numbers PRIVATE src)

set_target_properties(fun_with_numbers
  PROPERTIES
    CXX_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
 
target_link_libraries(fun_with_numbers
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)
