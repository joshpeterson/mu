#include <doctest.h>

#include <limits>
using std::numeric_limits;

#include "Interpreter/BinaryArithmeticOperation.hpp"
#include "Interpreter/Subtract.hpp"
#include "ValueStack.hpp"

void Subtract() {
  PerformBinaryOperation([](auto left, auto right) { return left - right; });
}

TEST_CASE("Verify subtract opcode behavior") {
  Push(42);
  Push(43);
  Subtract();
  CHECK(Pop().i32() == -1);
}

TEST_CASE("Verify subtract opcode behavior for 64-bit integers") {
  const int64_t left = numeric_limits<int64_t>::max() - 20;
  const int64_t right = 15;
  const int64_t expected = numeric_limits<int64_t>::max() - 35;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().i64() == expected);
}

TEST_CASE("Verify subtract opcode behavior for 32-bit floats") {
  Push(42.f);
  Push(43.f);
  Subtract();
  CHECK(Pop().f32() == -1.f);
}

TEST_CASE("Verify subtract opcode behavior for a 64-bit integer and a 32-bit "
          "integer") {
  const int64_t left = numeric_limits<int64_t>::max() - 20;
  const int32_t right = 15;
  const int64_t expected = numeric_limits<int64_t>::max() - 35;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().i64() == expected);
}

TEST_CASE("Verify subtract opcode behavior for a 32-bit integer and a 64-bit "
          "integer") {
  const int32_t left = 15;
  const int64_t right = numeric_limits<int64_t>::max();
  const int64_t expected = numeric_limits<int64_t>::min() + 16;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().i64() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 32-bit float and a 32-bit integer") {
  const float left = 20.f;
  const int32_t right = 15;
  const float expected = 5.f;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f32() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 32-bit integer and a 32-bit float") {
  const int32_t left = 15;
  const float right = 20.f;
  const float expected = -5.f;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f32() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 32-bit float and a 64-bit integer") {
  const float left = 15.f;
  const int64_t right = numeric_limits<int64_t>::max() - 20;
  const float expected = -(numeric_limits<int64_t>::max() - 5);
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f32() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 64-bit integer and a 32-bit float") {
  const int64_t left = numeric_limits<int64_t>::max() - 20;
  const float right = -15.f;
  const float expected = numeric_limits<int64_t>::max() - 5;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f32() == expected);
}

TEST_CASE("Verify subtract opcode 32-bit integer overflow") {
  const int32_t left = numeric_limits<int32_t>::min();
  const int32_t right = 1;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().i32() == numeric_limits<int32_t>::max());
}

TEST_CASE("Verify subtract opcode 64-bit integer overflow") {
  const int64_t left = numeric_limits<int64_t>::min();
  const int64_t right = 1;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().i64() == numeric_limits<int64_t>::max());
}