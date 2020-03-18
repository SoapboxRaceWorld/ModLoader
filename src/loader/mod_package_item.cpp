//
// Created by coder on 3/18/2020.
//

#include "mod_package_item.hpp"

mod_package_item::mod_package_item(std::wstring &path, mod_package_item_type type) : m_path_(path), m_type_(type) {

}

const std::wstring &mod_package_item::get_path() const {
    return m_path_;
}

mod_package_item_type mod_package_item::get_type() const {
    return m_type_;
}
