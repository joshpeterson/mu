#include "Configuration.hpp"

#include "StringUtils.hpp"

const string whitespace = " \n\r\t\f\v";

///
/// @brief Remove whitespace from the left of a string.
///
/// @param[in] s The string to trim.
/// @return string The trimmed string.
///
string TrimLeft(const string& s) {
  size_t start = s.find_first_not_of(whitespace);
  return (start == string::npos) ? "" : s.substr(start);
}

TEST_CASE("Removes whitepsace on the left") {
  CHECK("test  " == TrimLeft("  test  "));
}

///
/// @brief Remove whitespace from the right of a string.
///
/// @param[in] s The string to trim.
/// @return string The trimmed string.
///
string TrimRight(const string& s) {
  size_t end = s.find_last_not_of(whitespace);
  return (end == string::npos) ? "" : s.substr(0, end + 1);
}

TEST_CASE("Removes whitepsace on the right") {
  CHECK("  test" == TrimRight("  test  "));
}

///
/// @brief Remove whitespace from a string.
///
/// @param[in] s The string to trim.
/// @return string The trimmed string.
///
string Trim(const string& s) { return TrimRight(TrimLeft(s)); }

TEST_CASE("Removes whitepsace on the left and the right") {
  CHECK("test" == Trim("  test  "));
}
