//
// Created by coder on 3/17/2020.
//
#include "servertalk.hpp"

#define CPPHTTPLIB_ZLIB_SUPPORT
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <wincrypt.h>
#include "../httplib.hpp"
#include "../url.hpp"
#include <fmt/format.h>
#include <utility>

server_talk::server_talk(std::string server_address) : m_server_address_(std::move(server_address)) {
}

std::shared_ptr<server::modding_info> server_talk::get_modding_info() {
    // fix up address
    Url u1(m_server_address_);
    std::string address_base = fmt::format("{}://{}:{}", u1.scheme(), u1.host(), u1.port());

    auto res = httplib::Client2(address_base.c_str()).set_decompress(true).Get(
            (u1.path() + "/Modding/GetModInfo").c_str());
    auto body = res->body;

    if (res->status != 200 || body.empty()) {
        return nullptr;
    }

    nlohmann::json j = nlohmann::json::parse(body);

    return std::make_shared<server::modding_info>(j.get<server::modding_info>());
}
