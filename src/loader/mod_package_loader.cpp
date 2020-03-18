//
// Created by coder on 3/17/2020.
//

#include "mod_package_loader.hpp"
#include "mod_package_header.hpp"
#include <fstream>
#include <utility>
#include <bitextractor.hpp>
#include <bitexception.hpp>

static const unsigned char key_xor_table[] = {
        0x94, 0xce, 0xc3, 0xae, 0x73, 0xf9, 0xf1, 0xb9
};

mod_package_loader::mod_package_loader(fs::path path) : m_path_(std::move(path)) {

}

std::shared_ptr<mod_package> mod_package_loader::load() {
    std::ifstream stream(m_path_, std::ios::binary);

    if (!stream.good()) {
        return nullptr;
    }

    const auto file_size = fs::file_size(m_path_);

    if (file_size < sizeof(mod_package_header)) {
        return nullptr;
    }

    mod_package_header header{};

    stream.read((char *) &header, sizeof(mod_package_header));

    if (header.magic != 0x4459495A) {
        return nullptr;
    }

    const auto archive_size = file_size - sizeof(mod_package_header);

    if (archive_size == 0) {
        return nullptr;
    }

    std::string archive_key;

    if (header.encryption_enabled) {
        unsigned int key_length = 0;

        stream.read((char *) &key_length, sizeof(key_length));

        if (key_length != 32) {
            return nullptr;
        }

        unsigned char key[33] = {0};

        stream.read((char *) key, 32);

        for (int i = 0; i < 32; i++) {
            key[i] ^= key_xor_table[i % sizeof(key_xor_table)];
        }

        archive_key = std::string(key, key + 32);
    }

    // Set up 7z interface
    bit7z::Bit7zLibrary lib(L"7z.dll");
    bit7z::BitExtractor extractor(lib, bit7z::BitFormat::Zip);


    return nullptr;
}
