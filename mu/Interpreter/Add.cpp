#include "Configuration.hpp"

#include <limits>
using std::numeric_limits;

#include "Bytecode.hpp"
#include "Interpreter/Add.hpp"
#include "Interpreter/BinaryArithmeticOperation.hpp"
#include "ValueStack.hpp"

void Add() {
  PerformBinaryOperation([](auto left, auto right) { return left + right; });
}

InstructionMetadata GetAddMetadata() { return {.execute = Add, .name = "Add"}; }

TEST_CASE("Verify add opcode behavior") {
  SUBCASE("Verify add opcode behavior a 32-bit integer and a 32-bit integer") {
    const int32_t left = 42;
    const int32_t right = 43;
    const int32_t expected = 85;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().i32() == expected);
  }

  SUBCASE(
      "Verify add opcode behavior for a 32-bit integer and a 64-bit integer") {
    const int32_t left = 15;
    const int64_t right = numeric_limits<int64_t>::max() - 20;
    const int64_t expected = numeric_limits<int64_t>::max() - 5;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().i64() == expected);
  }

  SUBCASE(
      "Verify add opcode behavior for a 32-bit integer and a 32-bit float") {
    const int32_t left = 15;
    const float right = 20;
    const float expected = 35;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f32() == expected);
  }

  SUBCASE(
      "Verify add opcode behavior for a 32-bit integer and a 64-bit float") {
    const int32_t left = 15;
    const double right = 20;
    const double expected = 35;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f64() == expected);
  }

  SUBCASE("Verify add opcode behavior for a 64-bit integer and and 64-bit "
          "integer") {
    const int64_t left = numeric_limits<int64_t>::max() - 20;
    const int64_t right = 15;
    const int64_t expected = numeric_limits<int64_t>::max() - 5;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().i64() == expected);
  }

  SUBCASE(
      "Verify add opcode behavior for a 64-bit integer and a 32-bit integer") {
    const int64_t left = numeric_limits<int64_t>::max() - 20;
    const int32_t right = 15;
    const int64_t expected = numeric_limits<int64_t>::max() - 5;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().i64() == expected);
  }

  SUBCASE(
      "Verify add opcode behavior for a 64-bit integer and a 32-bit float") {
    const int64_t left = numeric_limits<int64_t>::max() - 20;
    const float right = 15;
    const float expected = numeric_limits<int64_t>::max() - 5;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f32() == expected);
  }

  SUBCASE(
      "Verify add opcode behavior for a 64-bit integer and a 64-bit float") {
    const int64_t left = numeric_limits<int64_t>::max() - 20;
    const double right = 15;
    const double expected = numeric_limits<int64_t>::max() - 5;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f64() == expected);
  }

  SUBCASE("Verify add opcode behavior for a 32-bit float and a 32-bit float") {
    const float left = 42;
    const float right = 43;
    const float expected = 85;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f32() == expected);
  }

  SUBCASE(
      "Verify add opcode behavior for a 32-bit float and a 32-bit integer") {
    const float left = 20;
    const int32_t right = 15;
    const float expected = 35;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f32() == expected);
  }

  SUBCASE(
      "Verify add opcode behavior for a 32-bit float and a 64-bit integer") {
    const float left = 15;
    const int64_t right = numeric_limits<int64_t>::max() - 20;
    const float expected = numeric_limits<int64_t>::max() - 5;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f32() == expected);
  }

  SUBCASE("Verify add opcode behavior for a 32-bit float and a 64-bit float") {
    const float left = 42;
    const double right = 43;
    const double expected = 85;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f64() == expected);
  }

  SUBCASE("Verify add opcode behavior for a 64-bit float and a 64-bit float") {
    const double left = 20;
    const double right = 15;
    const double expected = 35;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f64() == expected);
  }

  SUBCASE(
      "Verify add opcode behavior for a 64-bit float and and 64-bit integer") {
    const double left = numeric_limits<int64_t>::max() - 20;
    const int64_t right = 15;
    const double expected = numeric_limits<int64_t>::max() - 5;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f64() == expected);
  }

  SUBCASE(
      "Verify add opcode behavior for a 64-bit float and a 32-bit integer") {
    const double left = 20;
    const int32_t right = 15;
    const double expected = 35;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f64() == expected);
  }

  SUBCASE("Verify add opcode behavior for a 64-bit float and a 32-bit float") {
    const double left = 20;
    const float right = 15;
    const double expected = 35;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().f64() == expected);
  }

  SUBCASE("Verify add opcode 32-bit integer overflow") {
    const int32_t left = numeric_limits<int32_t>::max();
    const int32_t right = 1;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().i32() == numeric_limits<int32_t>::min());
  }

  SUBCASE("Verify add opcode 64-bit integer overflow") {
    const int64_t left = numeric_limits<int64_t>::max();
    const int64_t right = 1;
    Push(left);
    Push(right);
    Add();
    CHECK(Pop().i64() == numeric_limits<int64_t>::min());
  }
}

TEST_CASE("Verify add opcode performance") {
  ankerl::nanobench::Bench b;
  b.title(GetCurrentTestName()).relative(true);

  b.run("Baseline for add opcode", [] {
    auto x = 42 + 43;
    ankerl::nanobench::doNotOptimizeAway(x);
  });

  b.run("Add two integers", [] {
    Push(43);
    Push(42);
    Add();
  });

  b.run("Add two floats", [] {
    Push(43.4);
    Push(42.7);
    Add();
  });
}
