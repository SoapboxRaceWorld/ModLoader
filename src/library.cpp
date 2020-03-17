#include "stdafx.hpp"
#include <shellapi.h>

BOOL WINAPI InitializeModLoader() {
    LPWSTR *szArgList;
    int argCount;

    if ((szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount)) == nullptr) {
        MessageBoxW(nullptr, L"Failed to parse command line", L"Error", MB_OK);
        return FALSE;
    }

    if (argCount != 5) {
        MessageBoxW(nullptr, L"Invalid command line", L"Error", MB_OK);
        return FALSE;
    }

    const std::wstring server_url = szArgList[2];

    // TODO: get mod info

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