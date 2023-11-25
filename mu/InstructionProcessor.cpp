#include "Configuration.hpp"

#include <stdexcept>
using std::logic_error;

#include <fmt/core.h>
using fmt::format;

#include "Bytecode.hpp"
#include "InstructionProcessor.hpp"
#include "Interpreter/Interpreter.hpp"
#include "ValueStack.hpp"

/// == Instruction Processor ==
///
/// The instruction processor identifies each instruction and calls the proper
/// implemenatation for that instruction.

///
/// @brief Execute each instruction in the list, in the order they are given.
///
/// @param[in] instructions The list of instructions to execute.
///
void Process(span<Instruction> instructions) {
  for (auto& ins : instructions) {
    if (ins.opCode == OpCode::Push)
      Push(ins.argument);
    else if (ins.opCode == OpCode::Pop)
      Pop();
    else if (HasInstruction(ins.opCode))
      ExecuteInstruction(ins.opCode);
    else
      throw logic_error(format("Unexpected opcode: {}", (int)ins.opCode));
  }
}

TEST_CASE("Verify instruction processing behavior") {
  SUBCASE("Push two values and add") {
    Instruction instructions[] = {
        {OpCode::Push, 2}, {OpCode::Push, 3}, {OpCode::Add}};
    Process(instructions);
    CHECK(Pop().i32() == 5);
  }

  SUBCASE("Push three values, pop one and subtract") {
    // This should do 2 - 3
    Instruction instructions[] = {{OpCode::Push, 2},
                                  {OpCode::Push, 3},
                                  {OpCode::Push, 8},
                                  {OpCode::Pop},
                                  {OpCode::Subtract}};
    Process(instructions);
    CHECK(Pop().i32() == -1);
  }
}
