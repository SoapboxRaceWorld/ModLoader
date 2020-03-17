//
// Created by coder on 3/17/2020.
//

#include "modding_info.hpp"

void server::to_json(json& j, const server::modding_info& mi) {
    j = json{{"basePath", mi.basePath}, {"serverID", mi.serverID}, {"features", mi.features}};
}

void server::from_json(const json& j, server::modding_info& mi) {
    j.at("basePath").get_to(mi.basePath);
    j.at("serverID").get_to(mi.serverID);
    j.at("features").get_to(mi.features);
}