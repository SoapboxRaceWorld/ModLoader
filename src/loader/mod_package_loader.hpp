//
// Created by coder on 3/17/2020.
//

#ifndef MODLOADER_MOD_PACKAGE_LOADER_HPP
#define MODLOADER_MOD_PACKAGE_LOADER_HPP

#include <filesystem>
#include "mod_package.hpp"

namespace fs = std::filesystem;

class mod_package_loader {
public:
    explicit mod_package_loader(const fs::path& path);
    ~mod_package_loader() = default;

    std::shared_ptr<mod_package> load();
private:
    fs::path m_path_;
};


#endif //MODLOADER_MOD_PACKAGE_LOADER_HPP
