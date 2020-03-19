//
// Created by coder on 3/18/2020.
//

#ifndef MODLOADER_BYPASS_PATCHES_HPP
#define MODLOADER_BYPASS_PATCHES_HPP

#include "../Memory.hpp"

namespace bypass_patches {
    void apply() {
        // udp crc bypass
        Memory::writeRaw(0x367BF4, false, 1, 0xEB);
        // udp crypt function bypass read
        Memory::writeRaw(0x1C2797, false, 2, 0xEB, 0x46);
        // udp crypt function bypass send
        Memory::writeRaw(0x1C27E8, false, 2, 0xEB, 0xF5);
        // xmpp crc bypass
        Memory::writeRaw(0x13A490, false, 2, 0xEB, 0x2D);
    }
};

#endif //MODLOADER_BYPASS_PATCHES_HPP
