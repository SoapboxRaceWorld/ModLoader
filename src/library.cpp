#include "stdafx.hpp"
#include "utils.hpp"
#include "server/servertalk.hpp"
#include "loader/server_mod_loader.hpp"
#include "linker/mod_file_linker.hpp"
#include "patches/bypass_patches.hpp"
#include "patches/custom_crash_handler.hpp"

#include <shellapi.h>
#include <iostream>

void load_server_mods(std::shared_ptr<mod_file_linker> &linker, std::vector<mod_file_link_info> &links,
                      const std::shared_ptr<server::modding_info> &modding_info);

BOOL WINAPI InitializeModLoader() {
    LPWSTR *szArgList;
    int argCount;

    if ((szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount)) == nullptr) {
        MessageBoxW(nullptr, L"Failed to parse command line", L"Error", MB_OK | MB_ICONERROR);
        ExitProcess(1);
    }

    if (argCount != 5) {
        MessageBoxW(nullptr, L"Invalid command line", L"Error", MB_OK | MB_ICONERROR);
        ExitProcess(1);
    }

    const std::wstring server_url = szArgList[2];
    std::shared_ptr<mod_file_linker> linker = std::make_shared<mod_file_linker>();
    std::vector<mod_file_link_info> links;

    if (fs::exists(".links")) {
        MessageBoxW(nullptr, L".links file should not exist upon startup!", L"Error", MB_OK | MB_ICONERROR);
        ExitProcess(1);
    }

    try {
        const std::string cleaned_server_url = utf8_from_wstring(server_url);
        const auto server_talker = std::make_shared<server_talk>(cleaned_server_url);
        const auto modding_info = server_talker->get_modding_info();

        if (modding_info) {
            load_server_mods(linker, links, modding_info);
        }

        // Apply patches and hooks
        Memory::Init();
        bypass_patches::apply();
        crash_handler::install();
    } catch (const std::exception &exception) {
        MessageBoxA(nullptr, exception.what(), "Error", MB_OK | MB_ICONERROR);
        linker->revert_links(links);
        ExitProcess(1);
    }

    return TRUE;
}

void load_server_mods(std::shared_ptr<mod_file_linker> &linker, std::vector<mod_file_link_info> &links,
                      const std::shared_ptr<server::modding_info> &modding_info) {
    const auto loader = std::make_shared<server_mod_loader>(modding_info->serverID);
    std::vector<std::shared_ptr<mod_package>> packages = loader->load_packages();

    for (std::shared_ptr<mod_package> &package : packages) {
        for (const std::shared_ptr<mod_package_item> &package_entry : package->get_items()) {
            links.emplace_back(linker->add_link(package_entry));
        }
    }

    linker->write_link_info_file(".links");
}

BOOL WINAPI ShutDownModLoader() {
    // TODO: shutdown
    return TRUE;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            InitializeModLoader();
            break;
        case DLL_PROCESS_DETACH:
            ShutDownModLoader();
            break;
        default:
            break;
    }

    return TRUE;
}

#pragma clang diagnostic pop