#include "Configuration.hpp"

#include <cassert>
#include <limits>
using std::numeric_limits;

#include <fmt/core.h>
using fmt::format;

#include "Argument.hpp"

///
/// @brief Get the type of the Argument.
///
/// @return ArgumentType The type of the Argument.
///
ArgumentType Argument::Type() const { return m_Type; }

///
/// @brief Get the value of the Argument as a 32-bit integer.
/// This function should only be called if the ArgumentType is i32.
/// If the ArgumentType is not i32, this function will assert.
///
/// @return int32_t The value of the Argument as a 32-bit integer.
///
int32_t Argument::i32() const {
  assert(m_Type == ArgumentType::i32);
  return m_Data.i32;
}

///
/// @brief Get the value of the Argument as a 64-bit integer.
/// This function should only be called if the ArgumentType is i64.
/// If the ArgumentType is not i64, this function will assert.
///
/// @return int64_t The value of the Argument as a 64-bit integer.
///
int64_t Argument::i64() const {
  assert(m_Type == ArgumentType::i64);
  return m_Data.i64;
}

///
/// @brief Get the value of the Argument as a 32-bit float.
/// This function should only be called if the ArgumentType is i32.
/// If the ArgumentType is not i32, this function will assert.
///
/// @return int32_t The value of the Argument as a 32-bit float.
///
float Argument::f32() const {
  assert(m_Type == ArgumentType::f32);
  return m_Data.f32;
}

///
/// @brief Get the value of the Argument as a 64-bit float.
/// This function should only be called if the ArgumentType is i64.
/// If the ArgumentType is not i64, this function will assert.
///
/// @return int64_t The value of the Argument as a 64-bit float.
///
double Argument::f64() const {
  assert(m_Type == ArgumentType::f64);
  return m_Data.f64;
}

///
/// @brief Get the value of the Argument as a Boolean.
/// This function should only be called if the ArgumentType is b.
/// If the ArgumentType is not b, this function will assert.
///
/// @return bool The value of the Argument as a Boolean.
///
bool Argument::b() const {
  assert(m_Type == ArgumentType::b);
  return m_Data.b;
}

///
/// @brief Get the value of the Argument as an 8-bit character.
/// This function should only be called if the ArgumentType is c.
/// If the ArgumentType is not c, this function will assert.
///
/// @return char The value of the Argument as an 8-bit character.
///
char Argument::c() const {
  assert(m_Type == ArgumentType::c);
  return m_Data.c;
}

///
/// @brief Compare two Arguments for equality.
///
/// @param[in] left The left Argument to compare.
/// @param[in] right The right Argument to compare.
/// @return bool True if the Arguments are equal, false otherwise.
///
bool operator==(const Argument& left, const Argument& right) {
  if (left.Type() != right.Type())
    return false;

  if (left.Type() == ArgumentType::None && right.Type() == ArgumentType::None)
    return true;

  if (left.Type() == ArgumentType::i32)
    return left.i32() == right.i32();

  if (left.Type() == ArgumentType::i64)
    return left.i64() == right.i64();

  if (left.Type() == ArgumentType::f32)
    return left.f32() == right.f32();

  if (left.Type() == ArgumentType::f64)
    return left.f64() == right.f64();

  if (left.Type() == ArgumentType::b)
    return left.b() == right.b();

  if (left.Type() == ArgumentType::c)
    return left.c() == right.c();

  assert(0 && "Missing case for Argument equality");
  return false;
}

TEST_CASE("Verify argument behavior") {
  SUBCASE("Can get the type of a 32-bit integer") {
    Argument entry(0);
    CHECK(entry.Type() == ArgumentType::i32);
  }

  SUBCASE("Can get the type of a 64-bit integer") {
    Argument entry((int64_t)0);
    CHECK(entry.Type() == ArgumentType::i64);
  }

  SUBCASE("Can get the type of a 32-bit float") {
    Argument entry((float)0);
    CHECK(entry.Type() == ArgumentType::f32);
  }

  SUBCASE("Can get the type of a 64-bit float") {
    Argument entry((double)0);
    CHECK(entry.Type() == ArgumentType::f64);
  }

  SUBCASE("Can get the value of a 32-bit integer") {
    const int32_t expected = 42;
    Argument entry(expected);
    CHECK(entry.i32() == expected);
  }

  SUBCASE("Can get the value of a 64-bit integer") {
    const int64_t expected = numeric_limits<int64_t>::max() - 2;
    Argument entry(expected);
    CHECK(entry.i64() == expected);
  }

  SUBCASE("Can get the value of a 32-bit float") {
    const float expected = 42;
    Argument entry(expected);
    CHECK(entry.f32() == expected);
  }

  SUBCASE("Can get the value of a 64-bit float") {
    const double expected = 42;
    Argument entry(expected);
    CHECK(entry.f64() == expected);
  }

  SUBCASE("Can get the value of a boolean") {
    const bool expected = true;
    Argument entry(expected);
    CHECK(entry.b() == expected);
  }

  SUBCASE("Can get the value of a character") {
    const char expected = 'a';
    Argument entry(expected);
    CHECK(entry.c() == expected);
  }

  SUBCASE("An Argument i32 is equal to itself") {
    Argument entry(42);
    CHECK(entry == entry);
  }

  SUBCASE("An Argument i32 is equal to another Argument with the same value") {
    Argument entry1(42);
    Argument entry2(42);
    CHECK(entry1 == entry2);
  }

  SUBCASE("An Argument i32 is not equal to another Argument with the same type "
          "and a different value") {
    Argument entry1(42);
    Argument entry2(43);
    CHECK(entry1 != entry2);
  }

  SUBCASE("An Argument i64 is equal to itself") {
    Argument entry((int64_t)42);
    CHECK(entry == entry);
  }

  SUBCASE("An Argument i64 is equal to another Argument with the same value") {
    Argument entry1((int64_t)42);
    Argument entry2((int64_t)42);
    CHECK(entry1 == entry2);
  }

  SUBCASE("An Argument i64 is not equal to another Argument with the same type "
          "and a different value") {
    Argument entry1((int64_t)42);
    Argument entry2((int64_t)43);
    CHECK(entry1 != entry2);
  }

  SUBCASE("An Argument f32 is equal to itself") {
    Argument entry(42.f);
    CHECK(entry == entry);
  }

  SUBCASE("An Argument f32 is equal to another Argument with the same value") {
    Argument entry1(42.f);
    Argument entry2(42.f);
    CHECK(entry1 == entry2);
  }

  SUBCASE("An Argument f32 is not equal to another Argument with the same type "
          "and a different value") {
    Argument entry1(42.);
    Argument entry2(43.);
    CHECK(entry1 != entry2);
  }

  SUBCASE("An Argument f64 is equal to itself") {
    Argument entry(42.);
    CHECK(entry == entry);
  }

  SUBCASE("An Argument f64 is equal to another Argument with the same value") {
    Argument entry1(42.);
    Argument entry2(42.);
    CHECK(entry1 == entry2);
  }

  SUBCASE("An Argument f64 is not equal to another Argument with the same type "
          "and a different value") {
    Argument entry1(42.);
    Argument entry2(43.);
    CHECK(entry1 != entry2);
  }

  SUBCASE("An Argument boolean is equal to itself") {
    Argument entry(true);
    CHECK(entry == entry);
  }

  SUBCASE(
      "An Argument boolean is equal to another Argument with the same value") {
    Argument entry1(true);
    Argument entry2(true);
    CHECK(entry1 == entry2);
  }

  SUBCASE(
      "An Argument boolean is not equal to another Argument with the same type "
      "and a different value") {
    Argument entry1(true);
    Argument entry2(false);
    CHECK(entry1 != entry2);
  }

  SUBCASE("An Argument character is equal to itself") {
    Argument entry('a');
    CHECK(entry == entry);
  }

  SUBCASE("An Argument character is equal to another Argument with the same "
          "value") {
    Argument entry1('a');
    Argument entry2('a');
    CHECK(entry1 == entry2);
  }

  SUBCASE("An Argument character is not equal to another Argument with the "
          "same type "
          "and a different value") {
    Argument entry1('a');
    Argument entry2('b');
    CHECK(entry1 != entry2);
  }

  SUBCASE("Two empty Arguments are equal to each other") {
    Argument argument1;
    Argument argument2;
    CHECK(argument1 == argument2);
  }

  SUBCASE("Can format empty Argument") {
    Argument empty;
    CHECK("No argument" == format("{}", empty));
  }

  SUBCASE("Can format i32 Argument") {
    Argument argument(42);
    CHECK("42 (i32)" == format("{}", argument));
  }

  SUBCASE("Can format i64 Argument") {
    Argument argument((int64_t)42);
    CHECK("42 (i64)" == format("{}", argument));
  }

  SUBCASE("Can format f32 Argument") {
    Argument argument(42.f);
    CHECK("42 (f32)" == format("{}", argument));
  }

  SUBCASE("Can format f64 Argument") {
    Argument argument(42.);
    CHECK("42 (f64)" == format("{}", argument));
  }

  SUBCASE("Can format boolean Argument") {
    Argument argument(true);
    CHECK("true (bool)" == format("{}", argument));
  }

  SUBCASE("Can format character Argument") {
    Argument argument('a');
    CHECK("a (char)" == format("{}", argument));
  }
}
