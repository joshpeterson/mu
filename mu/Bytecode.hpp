#pragma once

#include <cstdint>

#include <string>
using std::string;

#include <fmt/format.h>

#include "Argument.hpp"

/// == Bytecode ==
///
/// The bytecode for μ is an array of instructions.
///
/// Each instruction has a unique opcode and an argument. The opcode identifes
/// which instruction should be executed. The argument is optional (some
/// instructions don't need an argument) and it ignored is not required.

///
/// @brief The definition of all opcodes that the VM can execute.
///
enum class OpCode {

  ///
  /// The nop opcode is special - it does nothing.
  ///
  Nop,

  /////////////////////////////////
  /// The push and pop opcodes are special - they implement value stack
  /// behavior.
  /////////////////////////////////

  ///
  /// Push a value onto the value stack.
  ///
  Push,

  ///
  /// Pop a value from the value stack.
  ///
  Pop,

  /////////////////////////////////
  /// These opcodes represent the actual instructions the VM can execute.
  /////////////////////////////////

  ///
  /// Add to integer or floating point values.
  ///
  Add,

  ///
  /// Add to integer or floating point values.
  ///
  Subtract
};

///
/// @brief An instruction for the VM to execute.
///
struct Instruction {
  ///
  /// The opcode for the instruction.
  ///
  OpCode opCode;

  ///
  /// The argument of the instruction.
  ///
  Argument argument;
};

///
/// @brief The type of a function that executes an instruction.
///
///
typedef void (*ExecuteInstructionFunc)();

///
/// @brief The metadata for an instruction.
///
struct InstructionMetadata {
  ///
  /// The function that executes the instruction.
  ///
  ExecuteInstructionFunc execute;

  ///
  /// The name of the instruction.
  ///
  string name;
};

void InitializeInstructions();

void RegisterInstruction(OpCode opCode, InstructionMetadata metadata);
bool HasInstruction(OpCode opCode);
OpCode GetOpCode(string name);
void ExecuteInstruction(OpCode opCode);
string GetInstructionName(OpCode opCode);

bool operator==(Instruction left, Instruction right);

///
/// @brief Format an opcode as a string, using the fmt library.
///
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

///
/// @brief Convert an opcode to string for the doctest library.
///
/// @param[in] value The opcide to convert to a string.
/// @return doctest::String The string representation of the opcode.
///
inline doctest::String toString(const OpCode& value) {
  return fmt::format("{}", value).c_str();
}
