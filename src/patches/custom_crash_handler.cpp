//
// Created by coder on 3/18/2020.
//

#include "custom_crash_handler.hpp"
#include "../Memory.hpp"
#include "../exception.hpp"
#include <detours.h>
#include <mutex>

#pragma comment(lib, "Dbghelp.lib")

static std::mutex exception_handler_mutex;

void WriteCrashTextDump(PEXCEPTION_POINTERS ExceptionInfo, SYSTEMTIME system_time, std::wstring &filename) {
    HANDLE hFile = CreateFileW(filename.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, CREATE_ALWAYS,
                               FILE_ATTRIBUTE_NORMAL,
                               nullptr);

    if (hFile != INVALID_HANDLE_VALUE) {
        auto Log = [ExceptionInfo, hFile](char *buffer, size_t size, bool reg, bool stack, bool trace) {
            if (LogException(buffer, size, static_cast<LPEXCEPTION_POINTERS>(ExceptionInfo), reg, stack, trace)) {
                DWORD NumberOfBytesWritten = 0;
                WriteFile(hFile, buffer, strlen(buffer), &NumberOfBytesWritten, nullptr);
            }
        };

        // Try to make a very descriptive exception, for that we need to malloc a huge buffer...
        if (auto buffer = static_cast<char *>(malloc(max_logsize_ever))) {
            Log(buffer, max_logsize_ever, true, true, true);
            free(buffer);
        } else {
            // Use a static buffer, no need for any allocation
            static const auto size = max_logsize_basic + max_logsize_regs + max_logsize_stackdump;
            static char static_buf[size];
            static_assert(size <= max_static_buffer, "Static buffer is too big");

            Log(buffer = static_buf, sizeof(static_buf), true, true, false);
        }

        CloseHandle(hFile);
    }
}

void WriteCrashMiniDump(PEXCEPTION_POINTERS ExceptionInfo, SYSTEMTIME system_time, std::wstring &filename) {
    MINIDUMP_EXCEPTION_INFORMATION exception_param;
    const auto dump_handle = CreateFileW(filename.c_str(), 0xC0000000, 3u, nullptr, 2u, 0, nullptr);
    if (dump_handle) {
        if (dump_handle != INVALID_HANDLE_VALUE) {
            exception_param.ThreadId = GetCurrentThreadId();
            exception_param.ExceptionPointers = ExceptionInfo;
            exception_param.ClientPointers = 1;
            const auto process_id = GetCurrentProcessId();
            const auto process = GetCurrentProcess();
            MiniDumpWriteDump(process, process_id, dump_handle, MiniDumpWithDataSegs, &exception_param, nullptr,
                              nullptr);
            CloseHandle(dump_handle);
        }
    }
}

std::wstring GetBaseDumpFileName(SYSTEMTIME system_time) {
    wchar_t lpFileName[0x104];
    swprintf_s(
            lpFileName,
            L"SBRCrashDump_CL%d_%04d.%02d.%02d_%02d.%02d.%02d",
            0,
            system_time.wYear,
            system_time.wMonth,
            system_time.wDay,
            system_time.wHour,
            system_time.wMinute,
            system_time.wSecond);
    return lpFileName;
}

LONG WINAPI CustomTopLevelExceptionFilter(PEXCEPTION_POINTERS ExceptionInfo) {
    exception_handler_mutex.lock();

    SYSTEMTIME system_time;
    GetSystemTime(&system_time);

    auto text_filename = GetBaseDumpFileName(system_time) + L".txt";
    auto mini_filename = GetBaseDumpFileName(system_time) + L".dmp";

    std::wstring error_message = L"A critical error in the game process has occurred and the game must exit. Send the following files (located in your game folder) to a developer:";
    error_message += '\n';
    error_message += L"- " + text_filename;
    error_message += '\n';
    error_message += L"- " + mini_filename;
    error_message += '\n';
    error_message += L"We hope to resolve your issue as soon as possible. Thanks for playing!";

    MessageBoxW(
            nullptr,
            error_message.c_str(),
            L"Critical error",
            MB_ICONERROR);
    WriteCrashMiniDump(ExceptionInfo, system_time, mini_filename);
    WriteCrashTextDump(ExceptionInfo, system_time, text_filename);
    TerminateProcess(GetCurrentProcess(), 1);
    return 1;
}

void crash_handler::install() {
    auto *origExceptionFilter = reinterpret_cast<decltype(UnhandledExceptionFilter) *>(Memory::makeAbsolute(0x2109D0));

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID &) origExceptionFilter, (PVOID) CustomTopLevelExceptionFilter);
    DetourTransactionCommit();
}
