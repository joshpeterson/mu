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

void Add() {
  assert(StackSize() >= 2);

  auto left = Pop();
  auto right = Pop();

  if (left.Type() == ArgumentType::i64 && right.Type() == ArgumentType::i64)
    Push(left.i64() + right.i64());
  else if (left.Type() == ArgumentType::i64 &&
           right.Type() == ArgumentType::i32)
    Push(left.i64() + right.i32());
  else if (left.Type() == ArgumentType::i32 &&
           right.Type() == ArgumentType::i64)
    Push(left.i32() + right.i64());
  else
    Push(left.i32() + right.i32());
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

void Subtract() {
  assert(StackSize() >= 2);

  auto right = Pop();
  auto left = Pop();

  if (left.Type() == ArgumentType::i64 && right.Type() == ArgumentType::i64)
    Push(left.i64() - right.i64());
  else if (left.Type() == ArgumentType::i64 &&
           right.Type() == ArgumentType::i32)
    Push(left.i64() - right.i32());
  else if (left.Type() == ArgumentType::i32 &&
           right.Type() == ArgumentType::i64)
    Push(left.i32() - right.i64());
  else
    Push(left.i32() - right.i32());
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