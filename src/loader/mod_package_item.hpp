//
// Created by coder on 3/18/2020.
//

#ifndef MODLOADER_MOD_PACKAGE_ITEM_HPP
#define MODLOADER_MOD_PACKAGE_ITEM_HPP

#include <string>

enum mod_package_item_type {
    Directory,
    File
};

class mod_package_item {
public:
    mod_package_item(std::wstring &path, mod_package_item_type type);

    [[nodiscard]] const std::wstring &get_path() const;

    [[nodiscard]] mod_package_item_type get_type() const;

private:
    std::wstring &m_path_;
    mod_package_item_type m_type_;
};


#endif //MODLOADER_MOD_PACKAGE_ITEM_HPP
