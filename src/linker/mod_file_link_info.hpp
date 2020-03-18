//
// Created by coder on 3/18/2020.
//

#ifndef MODLOADER_MOD_FILE_LINK_INFO_HPP
#define MODLOADER_MOD_FILE_LINK_INFO_HPP

#include <filesystem>

namespace fs = std::filesystem;

enum mod_file_link_type {
    FileLink = 0,
    DirectoryLink = 1,
    None = -1
};

struct mod_file_link_info {
    fs::path source_path;
    fs::path destination_path;
    mod_file_link_type type;
};

#endif //MODLOADER_MOD_FILE_LINK_INFO_HPP
