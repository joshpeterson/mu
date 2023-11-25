#include "Configuration.hpp"

#include <unordered_map>
using std::unordered_map;

#include "Bytecode.hpp"

#include "Interpreter/Add.hpp"
#include "Interpreter/Subtract.hpp"

static unordered_map<OpCode, InstructionMetadata> Instructions;

///
/// @brief Register all instructions that the VM can execute.
///
///
void InitializeInstructions() {
  RegisterInstruction(OpCode::Add, GetAddMetadata());
  RegisterInstruction(OpCode::Subtract, GetSubtractMetadata());
}

///
/// @brief Register a specific instruction.
///
/// @param[in] opCode The opcode of the instruction to register.
/// @param[in] metadata The metadata for the instruction to register.
///
void RegisterInstruction(OpCode opCode, InstructionMetadata metadata) {
  Instructions[opCode] = metadata;
}

///
/// @brief Check if an instruction exists for the given opcode.
///
/// @param[in] opCode The opcode to check for.
/// @return True if an instruction exists for the given opcode, false otherwise.
///
bool HasInstruction(OpCode opCode) { return Instructions.contains(opCode); }

///
/// @brief Find the opcode for the given instruction name.
///
/// @param[in] name The name of the instruction to find.
/// @return The opcode for the given instruction name.
///
OpCode GetOpCode(string name) {
  for (auto& [opCode, metadata] : Instructions) {
    if (metadata.name == name) {
      return opCode;
    }
  }

  return OpCode::Nop;
}

///
/// @brief Lookup the instruction for the given opcode and execute it.
///
/// @param[in] opCode The opcode of the instruction to execute.
///
void ExecuteInstruction(OpCode opCode) { Instructions[opCode].execute(); }

///
/// @brief Find the name of the instruction for the given opcode.
///
/// @param[in] opCode The opcode of the instruction to find the name of.
/// @return The name of the instruction for the given opcode.
///
string GetInstructionName(OpCode opCode) { return Instructions[opCode].name; }

///
/// @brief Determine if two instructions are equal.
///
/// @param[in] left One of the instructions to compare.
/// @param[in] right One of the instructions to compare.
/// @return True if the instructions are equal, false otherwise.
///
bool operator==(Instruction left, Instruction right) {
  return left.opCode == right.opCode && left.argument == right.argument;
}

bool MockInstructionCalled = false;
void MockInstruction() { MockInstructionCalled = true; }
InstructionMetadata MockInstructionMetadata = {.execute = MockInstruction,
                                               .name = "MockInstruction"};

TEST_CASE("Verify instruction registration behavior") {
  SUBCASE("Verify that instructions can be executed") {
    RegisterInstruction(OpCode::Nop, MockInstructionMetadata);
    ExecuteInstruction(OpCode::Nop);
    CHECK(MockInstructionCalled);
  }

  SUBCASE("Verify that instructions namecan be retrieved") {
    RegisterInstruction(OpCode::Nop, MockInstructionMetadata);
    CHECK(GetInstructionName(OpCode::Nop) == "MockInstruction");
  }

  SUBCASE("Verify that instructions can be checked for existence") {
    RegisterInstruction(OpCode::Nop, MockInstructionMetadata);
    CHECK(HasInstruction(OpCode::Nop));
  }

  SUBCASE("Verify that instructions can be retrieved by name") {
    RegisterInstruction(OpCode::Nop, MockInstructionMetadata);
    CHECK(GetOpCode("MockInstruction") == OpCode::Nop);
  }
}
