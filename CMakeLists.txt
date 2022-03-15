cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(cfconfig VERSION "0.0.1" DESCRIPTION "CLI clang-format configurator")

find_package(Clang REQUIRED clangFormat)

add_subdirectory(src)
