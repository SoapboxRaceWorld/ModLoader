//
// Created by coder on 3/17/2020.
//

#ifndef MODLOADER_MODDING_INFO_HPP
#define MODLOADER_MODDING_INFO_HPP

#include <nlohmann/json.hpp>

using nlohmann::json;

struct modding_info {
    std::string basePath;
    std::string serverID;
    std::vector<std::string> features;
};

void to_json(json& j, const modding_info& mi) {
    j = json{{"basePath", mi.basePath}, {"serverID", mi.serverID}, {"features", mi.features}};
}

void from_json(const json& j, modding_info& mi) {
    j.at("basePath").get_to(mi.basePath);
    j.at("serverID").get_to(mi.serverID);
    j.at("features").get_to(mi.features);
}

#endif //MODLOADER_MODDING_INFO_HPP
