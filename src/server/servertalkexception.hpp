//
// Created by coder on 3/17/2020.
//

#ifndef MODLOADER_SERVERTALKEXCEPTION_HPP
#define MODLOADER_SERVERTALKEXCEPTION_HPP

#include <exception>

class server_talk_exception : std::exception {
public:
    explicit server_talk_exception(const char *const message) : exception(message) {}
    explicit server_talk_exception(const std::string& message) : exception(message.c_str()) {}
};

#endif //MODLOADER_SERVERTALKEXCEPTION_HPP
