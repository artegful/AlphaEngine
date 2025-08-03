cmake_minimum_required(VERSION 3.5)
include(FetchContent)

project (AlphaEngine LANGUAGES CXX)

add_library(compile_flags INTERFACE)
target_compile_features(compile_flags INTERFACE cxx_std_20)

add_subdirectory(AlphaEngine)
add_subdirectory(Game)
add_subdirectory(Editor)