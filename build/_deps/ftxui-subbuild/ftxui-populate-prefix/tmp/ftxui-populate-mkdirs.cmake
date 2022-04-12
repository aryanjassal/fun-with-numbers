# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-src"
  "/home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-build"
  "/home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-subbuild/ftxui-populate-prefix"
  "/home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-subbuild/ftxui-populate-prefix/tmp"
  "/home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp"
  "/home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-subbuild/ftxui-populate-prefix/src"
  "/home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/aryanj/Projects/FunWithNumbers/build/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp/${subDir}")
endforeach()
