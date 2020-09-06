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
    fs::path extracted_path(item->get_extracted_path());

    link_info.source_path = local_path;
    link_info.destination_path = extracted_path;
    link_info.type = mod_file_link_type::None;

    // Ensure we are NOT trying to link a file twice. We only need to consider directories.
    {
        fs::path link_check_path = local_path;
        bool already_linked = false;

        while (link_check_path.has_parent_path()) {
            link_check_path = link_check_path.parent_path();
            if (m_link_map_[link_check_path]) {
                already_linked = true;
                break;
            }
        }

        if (already_linked) {
            return link_info;
        }
    }

    if (item->get_type() == mod_package_item_type::Directory) {
        if (!fs::is_directory(local_path)) {
            // Only try to link a directory if it doesn't already exist
            fs::create_directory_symlink(extracted_path, local_path);
            m_link_map_[local_path] = true;
            link_info.type = mod_file_link_type::DirectoryLink;
        } else {
            // Nothing to do.
            return link_info;
        }
    } else if (item->get_type() == mod_package_item_type::File) {
        // Make a backup first.
        if (fs::exists(local_path)) {
            fs::rename(local_path, fs::path(local_path).concat(".orig"));
        }

        fs::create_hard_link(extracted_path, local_path);
        link_info.type = mod_file_link_type::FileLink;
    }

    m_link_info_list_.emplace_back(link_info);
    return link_info;
}

void mod_file_linker::write_link_info_file(const fs::path &destination) {
    std::wofstream stream(destination, std::ios::trunc);
    for (const auto &link_info: m_link_info_list_) {
        stream << link_info.source_path.wstring() << '\t' << link_info.type << std::endl;
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

void mod_file_linker::revert_links() {
    for (const auto &link_info: m_link_info_list_) {
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

#pragma clang diagnostic pop