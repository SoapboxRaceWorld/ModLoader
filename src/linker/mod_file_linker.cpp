//
// Created by coder on 3/18/2020.
//

#include "mod_file_linker.hpp"
#include "mod_file_linker_exception.hpp"
#include <fstream>

void mod_file_linker::add_link(const std::shared_ptr<mod_package_item> item) {
    __asm int 3;
}

void mod_file_linker::write_link_info_file(const fs::path &destination) {
    std::wofstream stream(destination, std::ios::trunc);
    for (const auto &link_info: m_link_info_list_) {
        stream << link_info.destination_path << '\t' << link_info.type << std::endl;
    }
}
