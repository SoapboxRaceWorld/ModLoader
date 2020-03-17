//
// Created by coder on 3/17/2020.
//

#ifndef MODLOADER_MODDING_INFO_HPP
#define MODLOADER_MODDING_INFO_HPP

#include <nlohmann/json.hpp>

namespace server {
    using nlohmann::json;

    struct modding_info {
        std::string basePath;
        std::string serverID;
        std::vector<std::string> features;
    };

    void to_json(json& j, const modding_info& mi);
    void from_json(const json& j, modding_info& mi);
}

#endif //MODLOADER_MODDING_INFO_HPP
