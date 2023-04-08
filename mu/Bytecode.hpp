#pragma once

#include <cstdint>

#include <string>
using std::string;

#include <fmt/format.h>

#include "Argument.hpp"

// == Bytecode ==
//
// The bytecode for μ is an array of instructions.
//
// Each instruction has a unique opcode and an argument. The opcode identifes
// which instruction should be executed. The argument is optional (some
// instructions don't need an argument) and it ignored is not required.

enum class OpCode {
  Nop,

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
  Argument argument;
};

typedef void (*ExecuteInstructionFunc)();

struct InstructionMetadata {
  ExecuteInstructionFunc execute;
  string name;
};

void InitializeInstructions();

void RegisterInstruction(OpCode opCode, InstructionMetadata metadata);
bool HasInstruction(OpCode opCode);
OpCode GetOpCode(string name);
void ExecuteInstruction(OpCode opCode);
string GetInstructionName(OpCode opCode);

bool operator==(Instruction left, Instruction right);

template <> struct fmt::formatter<OpCode> : formatter<string_view> {
  // parse is inherited from formatter<string_view>.
  template <typename FormatContext>
  auto format(OpCode opCode, FormatContext& ctx) {
    string_view name = "unknown";
    if (opCode == OpCode::Nop)
      name = "Nop";
    else if (opCode == OpCode::Push)
      name = "Push";
    else if (opCode == OpCode::Pop)
      name = "Pop";
    else if (HasInstruction(opCode))
      name = GetInstructionName(opCode);

    return formatter<string_view>::format(name, ctx);
  }
};

inline doctest::String toString(const OpCode& value) {
  return fmt::format("{}", value).c_str();
}
