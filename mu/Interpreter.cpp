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
  i64 left = Pop();
  i64 right = Pop();
  Push(left + right);
}

TEST_CASE("Verify add opcode behavior") {
  Push(42);
  Push(43);
  Add();
  CHECK(Pop() == 85);
}

void Subtract() {
  assert(StackSize() >= 2);
  i64 right = Pop();
  i64 left = Pop();
  Push(left - right);
}

TEST_CASE("Verify subtract opcode behavior") {
  Push(42);
  Push(43);
  Subtract();
  CHECK(Pop() == -1);
}

