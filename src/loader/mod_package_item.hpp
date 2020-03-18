//
// Created by coder on 3/18/2020.
//

#ifndef MODLOADER_MOD_PACKAGE_ITEM_HPP
#define MODLOADER_MOD_PACKAGE_ITEM_HPP

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

enum mod_package_item_type {
    Directory,
    File
};

class mod_package_item {
public:
    mod_package_item(std::wstring &archive_path, fs::path &extracted_path, mod_package_item_type type);

    [[nodiscard]] const std::wstring &get_archive_path() const;

    [[nodiscard]] const fs::path &get_extracted_path() const;

    [[nodiscard]] mod_package_item_type get_type() const;

private:
    std::wstring &m_archive_path_;
    fs::path &m_extracted_path_;
    mod_package_item_type m_type_;
};


#endif //MODLOADER_MOD_PACKAGE_ITEM_HPP
