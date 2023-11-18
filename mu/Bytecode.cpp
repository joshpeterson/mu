#include "Configuration.hpp"

#include <unordered_map>
using std::unordered_map;

#include "Bytecode.hpp"

#include "Interpreter/Add.hpp"
#include "Interpreter/Subtract.hpp"

static unordered_map<OpCode, InstructionMetadata> Instructions;

void InitializeInstructions() {
  RegisterInstruction(OpCode::Add, GetAddMetadata());
  RegisterInstruction(OpCode::Subtract, GetSubtractMetadata());
}

void RegisterInstruction(OpCode opCode, InstructionMetadata metadata) {
  Instructions[opCode] = metadata;
}

bool HasInstruction(OpCode opCode) { return Instructions.contains(opCode); }

OpCode GetOpCode(string name) {
  for (auto& [opCode, metadata] : Instructions) {
    if (metadata.name == name) {
      return opCode;
    }
  }

  return OpCode::Nop;
}

void ExecuteInstruction(OpCode opCode) { Instructions[opCode].execute(); }

string GetInstructionName(OpCode opCode) { return Instructions[opCode].name; }

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
