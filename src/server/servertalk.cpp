//
// Created by coder on 3/17/2020.
//
#include "servertalk.hpp"
#include "servertalkexception.hpp"

#define CPPHTTPLIB_ZLIB_SUPPORT
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <wincrypt.h>
#include "../httplib.hpp"
//#include <cpr/cpr.h>
#include <fmt/format.h>
#include <utility>

server_talk::server_talk(std::string server_address) : m_server_address_(std::move(server_address)) {
}

std::shared_ptr<server::modding_info> server_talk::get_modding_info() {
    auto res = httplib::Client2(m_server_address_.c_str()).set_decompress(true).Get("/Modding/GetModInfo");
    auto body = res->body;

    if (res->status != 200 || body.empty()) {
        return nullptr;
    }

    MessageBoxA(nullptr, body.c_str(), "debug", MB_OK);

    nlohmann::json j = nlohmann::json::parse(body);

    return std::make_shared<server::modding_info>(j.get<server::modding_info>());
}
