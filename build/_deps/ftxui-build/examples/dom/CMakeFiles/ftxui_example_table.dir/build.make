# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aryanj/Projects/FunWithNumbers

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aryanj/Projects/FunWithNumbers/build

# Include any dependencies generated for this target.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/flags.make

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/table.cpp.o: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/flags.make
_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/table.cpp.o: _deps/ftxui-src/examples/dom/table.cpp
_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/table.cpp.o: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aryanj/Projects/FunWithNumbers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/table.cpp.o"
	cd /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-build/examples/dom && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/table.cpp.o -MF CMakeFiles/ftxui_example_table.dir/table.cpp.o.d -o CMakeFiles/ftxui_example_table.dir/table.cpp.o -c /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-src/examples/dom/table.cpp

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/table.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ftxui_example_table.dir/table.cpp.i"
	cd /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-build/examples/dom && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-src/examples/dom/table.cpp > CMakeFiles/ftxui_example_table.dir/table.cpp.i

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/table.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ftxui_example_table.dir/table.cpp.s"
	cd /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-build/examples/dom && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-src/examples/dom/table.cpp -o CMakeFiles/ftxui_example_table.dir/table.cpp.s

# Object files for target ftxui_example_table
ftxui_example_table_OBJECTS = \
"CMakeFiles/ftxui_example_table.dir/table.cpp.o"

# External object files for target ftxui_example_table
ftxui_example_table_EXTERNAL_OBJECTS =

_deps/ftxui-build/examples/dom/ftxui_example_table: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/table.cpp.o
_deps/ftxui-build/examples/dom/ftxui_example_table: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/build.make
_deps/ftxui-build/examples/dom/ftxui_example_table: _deps/ftxui-build/ftxui-dom.a
_deps/ftxui-build/examples/dom/ftxui_example_table: _deps/ftxui-build/ftxui-screen.a
_deps/ftxui-build/examples/dom/ftxui_example_table: _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aryanj/Projects/FunWithNumbers/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ftxui_example_table"
	cd /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-build/examples/dom && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ftxui_example_table.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/build: _deps/ftxui-build/examples/dom/ftxui_example_table
.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/build

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/clean:
	cd /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-build/examples/dom && $(CMAKE_COMMAND) -P CMakeFiles/ftxui_example_table.dir/cmake_clean.cmake
.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/clean

_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/depend:
	cd /home/aryanj/Projects/FunWithNumbers/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aryanj/Projects/FunWithNumbers /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-src/examples/dom /home/aryanj/Projects/FunWithNumbers/build /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-build/examples/dom /home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/ftxui-build/examples/dom/CMakeFiles/ftxui_example_table.dir/depend
