//
// Created by coder on 3/17/2020.
//

#include "mod_package.hpp"

#include <utility>

mod_package::mod_package(fs::path path, std::vector<std::shared_ptr<mod_package_item>> items) : m_path_(
        std::move(path)),
                                                                                                m_items_(std::move(
                                                                                                        items)) {
}

const fs::path &mod_package::get_path() const {
    return m_path_;
}

const std::vector<std::shared_ptr<mod_package_item>> &mod_package::get_items() const {
    return m_items_;
}

std::string mod_package::get_name() const {
    return m_path_.filename().stem().string();
}
