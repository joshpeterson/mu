#pragma once

#include <string>
using std::string_view;

#include <fmt/format.h>
using fmt::format;

void Log(string_view message);

template <typename... Args>
void Log(fmt::format_string<Args...> s, Args&&... args) {
  Log(fmt::format(s, std::forward<Args>(args)...));
}
