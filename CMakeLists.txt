cmake_minimum_required(VERSION 3.15)
project(ModLoader)

set(CMAKE_CXX_STANDARD 17)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)

add_subdirectory(libraries/bit7z)
target_include_directories(bit7z PUBLIC libraries/bit7z/include ${ZLIB_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
include_directories(libraries/detours/src)
link_directories(libraries/detours/lib.x86)
add_library(ModLoader SHARED src/Memory.hpp src/Memory.cpp src/library.cpp src/stdafx.hpp src/server/modding_info.hpp src/server/servertalk.cpp src/server/servertalk.hpp src/server/servertalkexception.hpp src/utils.hpp src/utils.cpp src/server/modding_info.cpp src/loader/mod_package_loader.cpp src/loader/mod_package_loader.hpp src/loader/mod_package.cpp src/loader/mod_package.hpp src/loader/server_mod_loader.cpp src/loader/server_mod_loader.hpp src/loader/mod_loader_exception.hpp src/md5.hpp src/md5.cpp src/loader/mod_package_header.hpp src/loader/mod_package_item.cpp src/loader/mod_package_item.hpp src/linker/mod_file_linker.cpp src/linker/mod_file_linker.hpp src/linker/mod_file_link_info.hpp src/linker/mod_file_linker_exception.hpp src/patches/bypass_patches.hpp src/patches/custom_crash_handler.hpp src/exception.hpp src/patches/custom_crash_handler.cpp src/httplib.hpp src/url.hpp src/url.cpp)
target_link_libraries(ModLoader PRIVATE cpr ZLIB::ZLIB fmt::fmt nlohmann_json bit7z detours ${ZLIB_LIBRARIES} ${OPENSSL_LIBRARIES})

set_target_properties(
        ModLoader
        PROPERTIES
        OUTPUT_NAME "ModLoader"
        SUFFIX ".asi"
)