//
// Created by coder on 3/18/2020.
//

#ifndef MODLOADER_MOD_FILE_LINKER_HPP
#define MODLOADER_MOD_FILE_LINKER_HPP

#include "../loader/mod_package_item.hpp"
#include "mod_file_link_info.hpp"
#include <vector>
#include <map>

class mod_file_linker {
public:
    mod_file_linker() = default;

    ~mod_file_linker() = default;

    mod_file_link_info add_link(std::shared_ptr<mod_package_item> item);

    mod_file_link_info add_link(mod_file_link_info item);

    void write_link_info_file(const fs::path &destination);

    void revert_links();

    static void revert_links(const std::vector<mod_file_link_info> &link_info_list);

private:
    std::vector<mod_file_link_info> m_link_info_list_;
    std::map<fs::path, bool> m_link_map_;
};


#endif //MODLOADER_MOD_FILE_LINKER_HPP
