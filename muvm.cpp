#include <cassert>
#include <span>
#include <stack>
#include <stdexcept>

#include <doctest.h>
#include <fmt/core.h>

using fmt::format;
using std::logic_error;
using std::span;
using std::stack;

// === μ Virtual Machine ===
//
// The μ VM is a stack based virtual machine. It has the following parts:
//
// * A set of instructions that define its operations
// * A value stack to store the values those instructions operate on
// * An interpreter that executes each instruction as a C++ function
// * A processing loop that dispatches each instruction to the interpreter
//
// Tests for each part of the VM are written immediately after the thing they
// test.

// == Instructions ==
//
// Each instruction has a unique opcode and an argument. The opcode identifes
// which instruction should be executed. The argument is optional (some
// instructions don't need an argument) and it ignored is not required.

enum class OpCode {
  // The push and pop opcodes are special - they implement value stack behavior.
  Push,
  Pop,

  // These opcodes represent the actual instructions the VM can execute.
  Add,
  Subtract
};

struct Instruction {
  OpCode opCode;
  int argument;
};

// == Value stack ==
//
// Each instruction operates on the value stack, poping values from the stack as
// it needs them and pushing results on to the stack. The value stack is free to
// grow and shrink as necessary to execute the instructions.

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

// == Interpreter ==
//
// The intrepreter provides an implementation for each instruction the VM can
// execute. Each instruction implementation is responsible to operating on the
// value stack properly.

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

// == Instruction processor ==
//
// The instruction processor identifies each instruction and calls the proper
// implemenatation for that instruction.

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
      throw logic_error(format("Unexpected opcode: {}", (int)ins.opCode));
  }
}

TEST_CASE("Verify instruction processing behavior") {
  SUBCASE("Push two values and add") {
    Instruction instructions[] = {
        {OpCode::Push, 2}, {OpCode::Push, 3}, {OpCode::Add}};
    Process(instructions);
    CHECK(Pop() == 5);
  }

  SUBCASE("Push three values, pop one and subtract") {
    // This should do 2 - 3
    Instruction instructions[] = {{OpCode::Push, 2},
                                  {OpCode::Push, 3},
                                  {OpCode::Push, 8},
                                  {OpCode::Pop},
                                  {OpCode::Subtract}};
    Process(instructions);
    CHECK(Pop() == -1);
  }
}

