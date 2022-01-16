#include <cassert>
#include <span>
#include <stack>
#include <vector>

#include "external/doctest/doctest.h"

using std::span;
using std::stack;
using std::vector;

namespace mu {

enum class OpCode { Push, Pop, Add, Subtract };

struct Instruction {
  OpCode opCode;
  int argument;
};

stack<int> valueStack;

void Push(int value) { valueStack.push(value); }

int Pop() {
  auto value = valueStack.top();
  valueStack.pop();
  return value;
}

int StackSize() { return valueStack.size(); }

TEST_CASE("Verify value stack behavior") {
  Push(42);
  CHECK(Pop() == 42);

  Push(43);
  CHECK(Pop() == 43);
}

void Add() {
  assert(StackSize() >= 2);
  int left = Pop();
  int right = Pop();
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
  int right = Pop();
  int left = Pop();
  Push(left - right);
}

TEST_CASE("Verify subtract opcode behavior") {
  Push(42);
  Push(43);
  Subtract();
  CHECK(Pop() == -1);
}

void Process(span<Instruction> instructions) {
  for (auto& ins : instructions) {
    if (ins.opCode == OpCode::Push)
      Push(ins.argument);
    else if (ins.opCode == OpCode::Pop)
      Pop();
    else if (ins.opCode == OpCode::Add)
      Add();
    else if (ins.opCode == OpCode::Subtract)
      Subtract();
    else
      assert(0 && "Unexpected OpCode");
  }
}

TEST_CASE("Verify instruction processing behavior") {
  SUBCASE("Push two values and add") {
    vector<Instruction> instructions = {
        {OpCode::Push, 2}, {OpCode::Push, 3}, {OpCode::Add}};
    Process(instructions);
    CHECK(Pop() == 5);
  }

  SUBCASE("Push three values, pop one and subtract") {
    // This should do 2 - 3
    vector<Instruction> instructions = {{OpCode::Push, 2},
                                        {OpCode::Push, 3},
                                        {OpCode::Push, 8},
                                        {OpCode::Pop},
                                        {OpCode::Subtract}};
    Process(instructions);
    CHECK(Pop() == -1);
  }
}

} // namespace mu

