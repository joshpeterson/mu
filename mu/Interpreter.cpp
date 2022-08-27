#include <doctest.h>

#include <cassert>

#include <limits>
using std::numeric_limits;

#include "Interpreter.hpp"
#include "ValueStack.hpp"

// == Interpreter ==
//
// The intrepreter provides an implementation for each instruction the VM can
// execute. Each instruction implementation is responsible to operating on the
// value stack properly.

// Binary arithmetic operations will all need to load instructions from the
// value stack in the same way. This define hides a bit of ugliness in C++,
// which does not allow function pointers to be defined from generic functions,
// but can allow one generic lambda to be used for multiple arguments. This
// means we cannot have just one argument to the implementation of the function
// which pulls values from the stack with the proper types. Instead, we hide
// that complexity with this macro.
#define PerformBinaryOperation(op) PerformBinaryOperationImpl(op, op, op, op)

typedef int32_t (*Operation3232)(int32_t, int32_t);
typedef int64_t (*Operation3264)(int32_t, int64_t);
typedef int64_t (*Operation6432)(int64_t, int32_t);
typedef int64_t (*Operation6464)(int64_t, int64_t);

void PerformBinaryOperationImpl(Operation3232 op3232, Operation3264 op3264,
                                Operation6432 op6432, Operation6464 op6464) {
  assert(StackSize() >= 2);

  auto right = Pop();
  auto left = Pop();

  if (left.Type() == ArgumentType::i64 && right.Type() == ArgumentType::i64)
    Push(op6464(left.i64(), right.i64()));
  else if (left.Type() == ArgumentType::i64 &&
           right.Type() == ArgumentType::i32)
    Push(op6432(left.i64(), right.i32()));
  else if (left.Type() == ArgumentType::i32 &&
           right.Type() == ArgumentType::i64)
    Push(op3264(left.i32(), right.i64()));
  else
    Push(op3232(left.i32(), right.i32()));
}

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

void Subtract() {
  auto subtract = [](auto left, auto right) { return left - right; };
  PerformBinaryOperation(subtract);
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

TEST_CASE("Verify subtract opcode 32-bit integer overflow") {
  const int32_t left = numeric_limits<int32_t>::min();
  const int32_t right = 1;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().i32() == numeric_limits<int32_t>::max());
}

TEST_CASE("Verify subtract add opcode 64-bit integer overflow") {
  const int64_t left = numeric_limits<int64_t>::min();
  const int64_t right = 1;
  Push(left);
  Push(right);
  Subtract();
  CHECK(Pop().i64() == numeric_limits<int64_t>::max());
}