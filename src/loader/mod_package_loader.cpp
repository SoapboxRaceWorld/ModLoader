//
// Created by coder on 3/17/2020.
//

#include "mod_package_loader.hpp"
#include "mod_package_header.hpp"
#include <fstream>
#include <utility>
#include <fmt/format.h>
#include "../stdafx.hpp"

mod_package_loader::mod_package_loader(fs::path path) : m_path_(std::move(path)) {

}

std::shared_ptr<mod_package> mod_package_loader::load() {
    std::ifstream stream(m_path_, std::ios::binary);

    if (!stream.good()) {
        return nullptr;
    }

    const auto file_size = fs::file_size(m_path_);

    if (file_size < sizeof(mod_package_header)) {
        return nullptr;
    }

    mod_package_header header{};

    stream.read((char *) &header, sizeof(mod_package_header));

    if (header.magic != 0x4459495A) {
        return nullptr;
    }

    const auto archive_size = file_size - sizeof(mod_package_header);

    if (archive_size == 0) {
        return nullptr;
    }


    return nullptr;
}
