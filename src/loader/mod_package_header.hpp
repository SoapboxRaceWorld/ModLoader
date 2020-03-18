//
// Created by coder on 3/17/2020.
//

#ifndef MODLOADER_MOD_PACKAGE_HEADER_HPP
#define MODLOADER_MOD_PACKAGE_HEADER_HPP

#include <cstdint>

struct mod_package_header {
    uint32_t magic;
    bool encryption_enabled;
    uint64_t compilation_timestamp;
};

static_assert(sizeof(mod_package_header) == 16, "sizeof(mod_package_header) should be 16!");

#endif //MODLOADER_MOD_PACKAGE_HEADER_HPP
