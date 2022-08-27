#include <doctest.h>

#include <cassert>
#include <limits>
using std::numeric_limits;

#include "Argument.hpp"

Argument::Argument() : m_Type(ArgumentType::None) {}

Argument::Argument(int32_t value) : m_Type(ArgumentType::i32) {
  m_Data.i32 = value;
}

Argument::Argument(int64_t value) : m_Type(ArgumentType::i64) {
  m_Data.i64 = value;
}

ArgumentType Argument::Type() const { return m_Type; }

int32_t Argument::i32() const {
  assert(m_Type == ArgumentType::i32);
  return m_Data.i32;
}

int64_t Argument::i64() const {
  assert(m_Type == ArgumentType::i64);
  return m_Data.i64;
}

bool operator==(const Argument& left, const Argument& right) {
  if (left.Type() != right.Type())
    return false;

  if (left.Type() == ArgumentType::None && right.Type() == ArgumentType::None)
    return true;

  if (left.Type() == ArgumentType::i32)
    return left.i32() == right.i32();

  if (left.Type() == ArgumentType::i64)
    return left.i64() == right.i64();

  assert(0 && "Missing case for Argument equality");
}

TEST_CASE("Can get the type of a 32-bit integer") {
  Argument entry(0);
  CHECK(entry.Type() == ArgumentType::i32);
}

TEST_CASE("Can get the type of a 64-bit integer") {
  Argument entry((int64_t)0);
  CHECK(entry.Type() == ArgumentType::i64);
}

TEST_CASE("Can get the value of a 32-bit integer") {
  const int32_t expected = 42;
  Argument entry(expected);
  CHECK(entry.i32() == expected);
}

TEST_CASE("Can get the value of a 64-bit integer") {
  const int64_t expected = numeric_limits<int64_t>::max() - 2;
  Argument entry(expected);
  CHECK(entry.i64() == expected);
}

TEST_CASE("A Argument i32 is equal to itself") {
  Argument entry(42);
  CHECK(entry == entry);
}

TEST_CASE("A Argument i32 is equal to another Argument with the same value") {
  Argument entry1(42);
  Argument entry2(42);
  CHECK(entry1 == entry2);
}

TEST_CASE("A Argument i32 is not equal to another Argument with the same type "
          "and a different value") {
  Argument entry1(42);
  Argument entry2(43);
  CHECK(entry1 != entry2);
}

TEST_CASE("A Argument i64 is equal to itself") {
  Argument entry((int64_t)42);
  CHECK(entry == entry);
}

TEST_CASE("A Argument i64 is equal to another Argument with the same value") {
  Argument entry1((int64_t)42);
  Argument entry2((int64_t)42);
  CHECK(entry1 == entry2);
}

TEST_CASE("A Argument i64 is not equal to another Argument with the same type "
          "and a different value") {
  Argument entry1((int64_t)42);
  Argument entry2((int64_t)43);
  CHECK(entry1 != entry2);
}

TEST_CASE("Two empty Arguments are equal to each other") {
  Argument argument1;
  Argument argument2;
  CHECK(argument1 == argument2);
}