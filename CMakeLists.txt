cmake_minimum_required(VERSION 3.15)
project(ModLoader)

set(CMAKE_CXX_STANDARD 14)
find_package(ZLIB)
find_package(cpr CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
add_library(ModLoader SHARED src/library.cpp src/stdafx.h)
target_link_libraries(ModLoader PRIVATE cpr ZLIB::ZLIB fmt::fmt)
set_target_properties(
        ModLoader
        PROPERTIES
        OUTPUT_NAME "ModLoader"
        SUFFIX ".asi"
)