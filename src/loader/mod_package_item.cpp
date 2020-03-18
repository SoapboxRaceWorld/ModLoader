//
// Created by coder on 3/18/2020.
//

#include "mod_package_item.hpp"

mod_package_item::mod_package_item(std::wstring &archive_path, fs::path &extracted_path, mod_package_item_type type)
        : m_archive_path_(archive_path), m_extracted_path_(extracted_path), m_type_(type) {

}

const std::wstring &mod_package_item::get_archive_path() const {
    return m_archive_path_;
}

mod_package_item_type mod_package_item::get_type() const {
    return m_type_;
}

const fs::path &mod_package_item::get_extracted_path() const {
    return m_extracted_path_;
}
