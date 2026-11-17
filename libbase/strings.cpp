/*
 * Copyright (C) 2023-2025 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstring>
#include <string>

namespace android {
namespace base {
bool StartsWith(const std::string& s, const char* prefix) {
    return strncmp(s.c_str(), prefix, strlen(prefix)) == 0;
}

// 自包含实现：不调用 A15 libbase 的模板 Trim(std::string_view)，避免垫片自身在
// 运行时又依赖某一版本 libbase 的模板实例化符号（否则加载到不含该模板的 libbase
// 时垫片自身会失败，达不到"给 libnvram 补旧 Trim"的目的）。语义与 android::base::Trim 一致。
std::string Trim(const std::string& s) {
    static const char* kWhitespace = " \t\n\v\f\r";
    const auto first = s.find_first_not_of(kWhitespace);
    if (first == std::string::npos) return std::string();
    const auto last = s.find_last_not_of(kWhitespace);
    return s.substr(first, last - first + 1);
}
}  // namespace base
}  // namespace android
