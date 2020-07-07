//
// Created by coder on 3/18/2020.
//

#include "mod_file_linker.hpp"
#include "mod_file_linker_exception.hpp"
#include <fstream>
#include <iostream>

mod_file_link_info
mod_file_linker::add_link(std::shared_ptr<mod_package_item> item) { // NOLINT(performance-unnecessary-value-param)
    mod_file_link_info link_info{};
    fs::path local_path(item->get_archive_path());

    link_info.source_path = item->get_archive_path();
    link_info.destination_path = item->get_extracted_path();

    if (item->get_type() == mod_package_item_type::File) {
        if (local_path.has_parent_path()) {
            // avoid double-links in the case of directories
            if (!m_link_map_[local_path.parent_path()]) {
                link_info.type = mod_file_link_type::FileLink;

                if (fs::exists(local_path)) {
                    // back up file
                    std::filesystem::path backup_path = local_path;
                    backup_path = backup_path.concat(".orig");
                    if (!fs::exists(backup_path)) {
                        fs::rename(local_path, backup_path);
                    }
                }

                fs::create_hard_link(item->get_extracted_path(), local_path);
            } else {
                link_info.type = mod_file_link_type::None;
                return link_info;
            }
        }
    } else {
        if (!fs::is_directory(local_path)) {
            link_info.type = mod_file_link_type::DirectoryLink;
            fs::create_directory_symlink(item->get_extracted_path(), local_path);
            m_link_map_[local_path] = true;
        } else {
            link_info.type = mod_file_link_type::None;
            return link_info;
        }
    }

    return this->add_link(link_info);
}

void mod_file_linker::write_link_info_file(const fs::path &destination) {
    std::wofstream stream(destination, std::ios::trunc);
    for (const auto &link_info: m_link_info_list_) {
        stream << link_info.source_path.wstring() << '\t' << link_info.type << std::endl;
    }
}

mod_file_link_info mod_file_linker::add_link(mod_file_link_info item) {
    m_link_info_list_.emplace_back(item);
    return item;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

void mod_file_linker::revert_links() {
    mod_file_linker::revert_links(m_link_info_list_);
}

#pragma clang diagnostic pop

void mod_file_linker::revert_links(const std::vector<mod_file_link_info> &link_info_list) {
    for (const auto &link_info: link_info_list) {
        if (!fs::exists(link_info.source_path)) {
            continue;
        }
        if (link_info.type == mod_file_link_type::DirectoryLink) {
            fs::remove(link_info.source_path);
        } else if (link_info.type == mod_file_link_type::FileLink) {
            fs::remove(link_info.source_path);
            std::filesystem::path backup_path = link_info.source_path;
            backup_path = backup_path.concat(".orig");
            if (fs::exists(backup_path)) {
                fs::rename(backup_path, link_info.source_path);
            }
        }
    }
}
