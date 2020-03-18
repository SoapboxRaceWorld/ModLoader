#include "stdafx.hpp"
#include "utils.hpp"
#include "server/servertalk.hpp"
#include "loader/server_mod_loader.hpp"
#include "linker/mod_file_linker.hpp"

#include <shellapi.h>
#include <iostream>

BOOL WINAPI InitializeModLoader() {
    LPWSTR *szArgList;
    int argCount;

    if ((szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount)) == nullptr) {
        MessageBoxW(nullptr, L"Failed to parse command line", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    if (argCount != 5) {
        MessageBoxW(nullptr, L"Invalid command line", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    const std::wstring server_url = szArgList[2];
    const auto linker = std::make_shared<mod_file_linker>();

    try {
        const std::string cleaned_server_url = utf8_from_wstring(server_url);
        const auto server_talker = std::make_shared<server_talk>(cleaned_server_url);
        const auto modding_info = server_talker->get_modding_info();

        if (modding_info) {
            const auto loader = std::make_shared<server_mod_loader>(modding_info->serverID);
            std::vector<std::shared_ptr<mod_package>> packages = loader->load_packages();

            for (std::shared_ptr<mod_package> &package : packages) {
                for (const std::shared_ptr<mod_package_item> &package_entry : package->get_items()) {
                    linker->add_link(package_entry);
                }
            }
        }
    } catch (const std::exception& exception) {
        MessageBoxA(nullptr, exception.what(), "Error", MB_OK | MB_ICONERROR);
        ExitProcess(1);
    }

    return TRUE;
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