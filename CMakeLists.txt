cmake_minimum_required(VERSION 3.5)
include(FetchContent)

project (AlphaEngine LANGUAGES CXX)

option(INCLUDE_EDITOR "Include editor into configuration (disable if no Qt is available)" ON)

add_library(compile_flags INTERFACE)
target_compile_features(compile_flags INTERFACE cxx_std_20)

add_subdirectory(AlphaEngine)
add_subdirectory(Game)

if (INCLUDE_EDITOR)
    add_subdirectory(Editor)
endif()