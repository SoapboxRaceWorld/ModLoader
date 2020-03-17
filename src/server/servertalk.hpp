//
// Created by coder on 3/17/2020.
//

#ifndef MODLOADER_SERVERTALK_HPP
#define MODLOADER_SERVERTALK_HPP

#include "../stdafx.hpp"
#include "modding_info.hpp"

class server_talk {
public:
    explicit server_talk(std::string  server_address);
    ~server_talk() = default;

    std::shared_ptr<modding_info> get_modding_info();
private:
    std::string m_server_address_;
};


#endif //MODLOADER_SERVERTALK_HPP
