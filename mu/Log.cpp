#include "Configuration.hpp"

#include "Log.hpp"

using fmt::print;

///
/// @brief Display a message to standard output. The message will be prepended
/// with text indicating that it is from the mu VM.
///
/// @param[in] message The message to output.
///
void Log(string_view message) { print("[=== \u03BC ===] {}\n", message); }
