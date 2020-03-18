//
// Created by coder on 3/17/2020.
//

#include "server_mod_loader.hpp"
#include "mod_loader_exception.hpp"
#include "mod_package_loader.hpp"
#include "../md5.hpp"
#include <filesystem>
#include <fmt/format.h>
#include <utility>

namespace fs = std::filesystem;

server_mod_loader::server_mod_loader(std::string server_id) : m_server_id_(std::move(server_id)) {
}

void server_mod_loader::load_packages() {
    const auto server_id_hash = md5(m_server_id_);
    const auto server_mod_directory = fs::current_path() / "MODS" / server_id_hash;

    if (fs::is_directory(server_mod_directory)) {
        for (const auto &server_mod_directory_entry : fs::directory_iterator(server_mod_directory)) {
            const auto &path = server_mod_directory_entry.path();

            if (path.extension() != ".mods") {
                throw mod_loader_exception(fmt::format("Unexpected file detected: {0}", path.filename().generic_string()));
            }

            const auto loader = std::make_shared<mod_package_loader>(path);
            const auto package = loader->load();

            if (!package) {
                throw mod_loader_exception(fmt::format("Could not load package: {0}", path.filename().generic_string()));
            }
        }
    } else {
        throw mod_loader_exception(fmt::format("Could not find mods for server: {0}", m_server_id_));
    }
}
