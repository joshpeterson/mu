#include <doctest.h>

#include <cassert>

#include "Interpreter.hpp"
#include "ValueStack.hpp"

// == Interpreter ==
//
// The intrepreter provides an implementation for each instruction the VM can
// execute. Each instruction implementation is responsible to operating on the
// value stack properly.

void Add() {
  assert(StackSize() >= 2);
  int64_t left = get<int64_t>(Pop());
  int64_t right = get<int64_t>(Pop());
  Push(left + right);
}

TEST_CASE("Verify add opcode behavior") {
  Push(42);
  Push(43);
  Add();
  CHECK(get<int64_t>(Pop()) == 85);
}

void Subtract() {
  assert(StackSize() >= 2);
  int64_t right = get<int64_t>(Pop());
  int64_t left = get<int64_t>(Pop());
  Push(left - right);
}

TEST_CASE("Verify subtract opcode behavior") {
  Push(42);
  Push(43);
  Subtract();
  CHECK(get<int64_t>(Pop()) == -1);
}
