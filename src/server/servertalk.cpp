//
// Created by coder on 3/17/2020.
//

#include "servertalk.hpp"
#include "servertalkexception.hpp"

#include <cpr/cpr.h>
#include <fmt/format.h>
#include <utility>

server_talk::server_talk(std::string server_address) : m_server_address_(std::move(server_address)) {
}

std::shared_ptr<server::modding_info> server_talk::get_modding_info() {
    auto r = cpr::Get(cpr::Url{m_server_address_ + "/Modding/GetModInfo"});

    if (r.error) {
        throw server_talk_exception(fmt::format("GetModInfo() failed with code {0}", r.error.code));
    }

    if (r.status_code != 200 || r.text.empty()) {
        return nullptr;
    }


    nlohmann::json j = nlohmann::json::parse(r.text);

    return std::make_shared<server::modding_info>(j.get<server::modding_info>());
}
