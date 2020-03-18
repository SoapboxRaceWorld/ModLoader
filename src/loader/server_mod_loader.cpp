//
// Created by coder on 3/17/2020.
//

#include "server_mod_loader.hpp"
#include "mod_loader_exception.hpp"
#include "mod_package_loader.hpp"
#include "../md5.hpp"
#include <filesystem>
#include <fmt/format.h>

namespace fs = std::filesystem;

server_mod_loader::server_mod_loader(std::string &server_id) : m_server_id_(server_id) {
}

std::vector<std::shared_ptr<mod_package>> server_mod_loader::load_packages() {
    std::vector<std::shared_ptr<mod_package>> packages;

    const auto server_id_hash = md5(m_server_id_);
    const auto server_mod_directory = fs::current_path() / "MODS" / server_id_hash;

    if (fs::is_directory(server_mod_directory)) {
        for (const auto &server_mod_directory_entry : fs::directory_iterator(server_mod_directory)) {
            auto &path = server_mod_directory_entry.path();

            if (path.extension() != ".mods") {
                throw mod_loader_exception(
                        fmt::format("Unexpected file detected: {0}", path.filename().generic_string()));
            }

            const auto loader = std::make_shared<mod_package_loader>(m_server_id_, const_cast<fs::path &>(path));
            std::shared_ptr<mod_package> package = loader->load();

            if (!package) {
                throw mod_loader_exception(
                        fmt::format("Could not load package: {0}", path.filename().generic_string()));
            }

            auto items = package->get_items();

            packages.emplace_back(package);
        }
    } else {
        throw mod_loader_exception(fmt::format("Could not find mods for server: {0}", m_server_id_));
    }

    return packages;
}
