#include <doctest.h>

#include "StringUtils.hpp"

const string whitespace = " \n\r\t\f\v";

string TrimLeft(const string& s) {
  size_t start = s.find_first_not_of(whitespace);
  return (start == string::npos) ? "" : s.substr(start);
}

TEST_CASE("Removes whitepsace on the left") {
  CHECK("test  " == TrimLeft("  test  "));
}

string TrimRight(const string& s) {
  size_t end = s.find_last_not_of(whitespace);
  return (end == string::npos) ? "" : s.substr(0, end + 1);
}

TEST_CASE("Removes whitepsace on the right") {
  CHECK("  test" == TrimRight("  test  "));
}

string Trim(const string& s) { return TrimRight(TrimLeft(s)); }

TEST_CASE("Removes whitepsace on the left and the right") {
  CHECK("test" == Trim("  test  "));
}
