//
// Created by coder on 3/17/2020.
//

#include "server_mod_loader.hpp"
#include <filesystem>
#include <utility>

namespace fs = std::filesystem;

server_mod_loader::server_mod_loader(std::string server_id) : m_server_id_(std::move(server_id)) {
}

void server_mod_loader::load_packages() {
    // TODO: get directory
}
