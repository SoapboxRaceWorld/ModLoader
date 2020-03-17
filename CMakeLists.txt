cmake_minimum_required(VERSION 3.15)
project(ModLoader)

set(CMAKE_CXX_STANDARD 14)

add_library(ModLoader SHARED library.cpp stdafx.h)
set_target_properties(
        ModLoader
        PROPERTIES
        OUTPUT_NAME "ModLoader"
        SUFFIX ".asi"
)