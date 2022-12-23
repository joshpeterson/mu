#include "Log.hpp"

using fmt::print;

void Log(string_view message) { print("[=== \u03BC ===] {}\n", message); }