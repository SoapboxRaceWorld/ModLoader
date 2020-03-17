//
// Created by coder on 3/17/2020.
//

#include <codecvt>

std::string utf8_from_wstring(const std::wstring &str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> char_converter;
    return char_converter.to_bytes(str);
}

std::wstring utf8_to_wstring(const std::string &str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> char_converter;
    return char_converter.from_bytes(str);
}
