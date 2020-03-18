//
// Created by coder on 3/17/2020.
//

#include "mod_package_loader.hpp"

mod_package_loader::mod_package_loader(const fs::path &path) : m_path_(path) {

}

std::shared_ptr<mod_package> mod_package_loader::load() {
    return nullptr;
}
