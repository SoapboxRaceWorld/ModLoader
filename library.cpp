#include "stdafx.h"

BOOL WINAPI InitializeModLoader() {
    // TODO: initialization
    return TRUE;
}

BOOL WINAPI ShutDownModLoader() {
    // TODO: shutdown
    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD fdwReason, LPVOID lpvReserved) {
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