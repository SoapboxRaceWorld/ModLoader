//
// Created by coder on 3/17/2020.
//

#ifndef MODLOADER_SERVER_MOD_LOADER_HPP
#define MODLOADER_SERVER_MOD_LOADER_HPP

#include <vector>
#include <memory>
#include "mod_package.hpp"

class server_mod_loader {
public:
    explicit server_mod_loader(std::string &server_id);

    ~server_mod_loader() = default;

    std::vector<std::shared_ptr<mod_package>> load_packages();

private:
    std::string &m_server_id_;
};


#endif //MODLOADER_SERVER_MOD_LOADER_HPP
