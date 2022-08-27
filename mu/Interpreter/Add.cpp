#include <doctest.h>

#include <limits>
using std::numeric_limits;

#include "Interpreter/Add.hpp"
#include "Interpreter/BinaryArithmeticOperation.hpp"
#include "ValueStack.hpp"

void Add() {
  auto add = [](auto left, auto right) { return left + right; };
  PerformBinaryOperation(add);
}

TEST_CASE("Verify add opcode behavior for 32-bit integers") {
  Push(42);
  Push(43);
  Add();
  CHECK(Pop().i32() == 85);
}

TEST_CASE("Verify add opcode behavior for 64-bit integers") {
  const int64_t left = numeric_limits<int64_t>::max() - 20;
  const int64_t right = 15;
  const int64_t expected = numeric_limits<int64_t>::max() - 5;
  Push(left);
  Push(right);
  Add();
  CHECK(Pop().i64() == expected);
}

TEST_CASE(
    "Verify add opcode behavior for a 64-bit integer and a 32-bit integer") {
  const int64_t left = numeric_limits<int64_t>::max() - 20;
  const int32_t right = 15;
  const int64_t expected = numeric_limits<int64_t>::max() - 5;
  Push(left);
  Push(right);
  Add();
  CHECK(Pop().i64() == expected);
}

TEST_CASE(
    "Verify add opcode behavior for a 32-bit integer and a 64-bit integer") {
  const int32_t left = 15;
  const int64_t right = numeric_limits<int64_t>::max() - 20;
  const int64_t expected = numeric_limits<int64_t>::max() - 5;
  Push(left);
  Push(right);
  Add();
  CHECK(Pop().i64() == expected);
}

TEST_CASE("Verify add opcode 32-bit integer overflow") {
  const int32_t left = numeric_limits<int32_t>::max();
  const int32_t right = 1;
  Push(left);
  Push(right);
  Add();
  CHECK(Pop().i32() == numeric_limits<int32_t>::min());
}

TEST_CASE("Verify add opcode 64-bit integer overflow") {
  const int64_t left = numeric_limits<int64_t>::max();
  const int64_t right = 1;
  Push(left);
  Push(right);
  Add();
  CHECK(Pop().i64() == numeric_limits<int64_t>::min());
}