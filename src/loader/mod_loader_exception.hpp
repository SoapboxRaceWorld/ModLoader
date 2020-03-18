//
// Created by coder on 3/17/2020.
//

#ifndef MODLOADER_MODLOADEREXCEPTION_HPP
#define MODLOADER_MODLOADEREXCEPTION_HPP

#include <exception>
#include "../stdafx.hpp"

class mod_loader_exception : public std::exception {
public:
    explicit mod_loader_exception(const char *const message) : exception(message) {}
    explicit mod_loader_exception(const std::string& message) : exception(message.c_str()) {}
};

#endif //MODLOADER_MODLOADEREXCEPTION_HPP
