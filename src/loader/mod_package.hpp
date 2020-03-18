//
// Created by coder on 3/17/2020.
//

#ifndef MODLOADER_MOD_PACKAGE_HPP
#define MODLOADER_MOD_PACKAGE_HPP

#include <filesystem>
#include "mod_package_item.hpp"

namespace fs = std::filesystem;

class mod_package {
public:
    mod_package(fs::path path, std::vector<std::shared_ptr<mod_package_item>> items);

    ~mod_package() = default;

    [[nodiscard]] const fs::path &get_path() const;

    [[nodiscard]] const std::vector<std::shared_ptr<mod_package_item>> &get_items() const;

    [[nodiscard]] std::string get_name() const;

private:
    fs::path m_path_;
    std::vector<std::shared_ptr<mod_package_item>> m_items_;
};


#endif //MODLOADER_MOD_PACKAGE_HPP
