//
// Created by coder on 3/18/2020.
//

#ifndef MODLOADER_MOD_FILE_LINKER_EXCEPTION_HPP
#define MODLOADER_MOD_FILE_LINKER_EXCEPTION_HPP

#include <exception>
#include <string>

class mod_file_linker_exception : public std::exception {
public:
    explicit mod_file_linker_exception(const char *const message) : exception(message) {}

    explicit mod_file_linker_exception(const std::string &message) : exception(message.c_str()) {}
};

#endif //MODLOADER_MOD_FILE_LINKER_EXCEPTION_HPP
