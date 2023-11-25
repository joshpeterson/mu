#pragma once

#include <string>
using std::string_view;

#include <fmt/format.h>
using fmt::format;

void Log(string_view message);

///
/// @brief Display a formatted message, using the fmt library to standard
/// output. The message will be prepended with text indicating that it is from
/// the mu VM.
///
/// @tparam Args Avoid providing template arguments directly, the compiler will
/// infer them.
/// @param[in] s The format string to output.
/// @param[in] args The format arguments, which will be substituted into the
/// format string.
///
template <typename... Args>
void Log(fmt::format_string<Args...> s, Args&&... args) {
  Log(fmt::format(s, std::forward<Args>(args)...));
}
