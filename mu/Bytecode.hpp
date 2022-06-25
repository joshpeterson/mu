#pragma once

#include <cstdint>

// == Bytecode ==
//
// The bytecode for μ is an array of instructions.
//
// Each instruction has a unique opcode and an argument. The opcode identifes
// which instruction should be executed. The argument is optional (some
// instructions don't need an argument) and it ignored is not required.

typedef int64_t i64;

enum class OpCode {
  // The push and pop opcodes are special - they implement value stack
  // behavior.
  Push,
  Pop,

  // These opcodes represent the actual instructions the VM can execute.
  Add,
  Subtract
};

struct Instruction {
  OpCode opCode;
  i64 argument;
};

inline bool operator==(Instruction left, Instruction right) {
  return left.opCode == right.opCode && left.argument == right.argument;
}

