#include <doctest.h>

#include <limits>
using std::numeric_limits;

#include "Interpreter/BinaryArithmeticOperation.hpp"
#include "Interpreter/Subtract.hpp"
#include "ValueStack.hpp"

void Subtract() {
  PerformBinaryOperation([](auto left, auto right) { return left - right; });
}

TEST_CASE("Verify subtract opcode behavior for a 32-bit integer and a 32-bit "
          "integer") {
  const int32_t left = 42;
  const int32_t right = 43;
  const int32_t expected = -1;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().i32() == expected);
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
    "Verify subtract opcode behavior for a 32-bit integer and a 32-bit float") {
  const int32_t left = 15;
  const float right = 20;
  const float expected = -5;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f32() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 32-bit integer and a 64-bit float") {
  const int32_t left = 15;
  const double right = 20;
  const double expected = -5;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f64() == expected);
}

TEST_CASE("Verify subtract opcode behavior for a 64-bit integer and a 64-bit "
          "integer") {
  const int64_t left = numeric_limits<int64_t>::max() - 20;
  const int64_t right = 15;
  const int64_t expected = numeric_limits<int64_t>::max() - 35;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().i64() == expected);
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

TEST_CASE(
    "Verify subtract opcode behavior for a 64-bit integer and a 32-bit float") {
  const int64_t left = numeric_limits<int64_t>::max() - 20;
  const float right = -15;
  const float expected = numeric_limits<int64_t>::max() - 5;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f32() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 64-bit integer and a 64-bit float") {
  const int64_t left = numeric_limits<int64_t>::max() - 20;
  const double right = -15;
  const double expected = numeric_limits<int64_t>::max() - 5;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f64() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 32-bit float and a 32-bit float") {
  const float left = 42;
  const float right = 43;
  const float expected = -1;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f32() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 32-bit float and a 32-bit integer") {
  const float left = 20;
  const int32_t right = 15;
  const float expected = 5;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f32() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 32-bit float and a 64-bit integer") {
  const float left = 15;
  const int64_t right = numeric_limits<int64_t>::max() - 20;
  const float expected = -(numeric_limits<int64_t>::max() - 5);
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f32() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 32-bit float and a 64-bit float") {
  const float left = 42;
  const double right = 43;
  const double expected = -1;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f64() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 64-bit float and a 64-bit float") {
  const double left = 20;
  const double right = -15;
  const double expected = 35;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f64() == expected);
}

TEST_CASE("Verify subtract opcode behavior for a 64-bit float and a 64-bit "
          "integer") {
  const double left = 20;
  const int64_t right = 15;
  const double expected = 5;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f64() == expected);
}

TEST_CASE("Verify subtract opcode behavior for a 64-bit float and a 32-bit "
          "integer") {
  const double left = 20;
  const int32_t right = 15;
  const double expected = 5;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f64() == expected);
}

TEST_CASE(
    "Verify subtract opcode behavior for a 64-bit float and a 32-bit float") {
  const double left = 20;
  const float right = -15;
  const double expected = 35;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().f64() == expected);
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