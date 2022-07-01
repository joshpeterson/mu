#pragma once

#include <cstdint>

#include <fmt/format.h>

// == Bytecode ==
//
// The bytecode for μ is an array of instructions.
//
// Each instruction has a unique opcode and an argument. The opcode identifes
// which instruction should be executed. The argument is optional (some
// instructions don't need an argument) and it ignored is not required.

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
  int64_t argument;
};

inline bool operator==(Instruction left, Instruction right) {
  return left.opCode == right.opCode && left.argument == right.argument;
}

template <> struct fmt::formatter<OpCode> : formatter<string_view> {
  // parse is inherited from formatter<string_view>.
  template <typename FormatContext> auto format(OpCode c, FormatContext& ctx) {
    string_view name = "unknown";
    switch (c) {
    case OpCode::Push:
      name = "Push";
      break;
    case OpCode::Pop:
      name = "Pop";
      break;
    case OpCode::Add:
      name = "Add";
      break;
    case OpCode::Subtract:
      name = "Subtract";
      break;
    }
    return formatter<string_view>::format(name, ctx);
  }
};
