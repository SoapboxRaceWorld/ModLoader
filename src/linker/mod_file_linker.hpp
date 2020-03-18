//
// Created by coder on 3/18/2020.
//

#ifndef MODLOADER_MOD_FILE_LINKER_HPP
#define MODLOADER_MOD_FILE_LINKER_HPP

#include "../loader/mod_package_item.hpp"
#include "mod_file_link_info.hpp"
#include <vector>

class mod_file_linker {
public:
    mod_file_linker() = default;

    ~mod_file_linker() = default;

    void add_link(std::shared_ptr<mod_package_item> item);

    void write_link_info_file(const fs::path &destination);

private:
    std::vector<mod_file_link_info> m_link_info_list_;
};


#endif //MODLOADER_MOD_FILE_LINKER_HPP
