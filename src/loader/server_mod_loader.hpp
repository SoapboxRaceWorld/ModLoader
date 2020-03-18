//
// Created by coder on 3/17/2020.
//

#ifndef MODLOADER_SERVER_MOD_LOADER_HPP
#define MODLOADER_SERVER_MOD_LOADER_HPP

#include "../stdafx.hpp"

class server_mod_loader {
public:
    explicit server_mod_loader(std::string  server_id);
    ~server_mod_loader() = default;

    void load_packages();
private:
    std::string m_server_id_;
};


#endif //MODLOADER_SERVER_MOD_LOADER_HPP
