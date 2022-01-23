#pragma once

// == Bytecode ==
//
// The bytecode for μ is an array of instructions.
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

