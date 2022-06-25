#include "TestUtilities.hpp"
#include <doctest.h>

#include "Loader.hpp"

// == Loader ==
//
// Instructions can be loaded from a binary file. This lass opens that file
// and provides a list of instructions to be executed. It closes the file
// when the instance of the Loadrer does out of scope.

Loader::Loader(const char* muFilePath) : m_muFile(muFilePath) {
  auto numberOfInstructions = m_muFile.GetSize() / sizeof(Instruction);
  m_instructions = span<Instruction>{(Instruction*)m_muFile.GetBuffer(),
                                     numberOfInstructions};
}

span<Instruction> Loader::GetInstructions() const { return m_instructions; }

TEST_CASE("Verify loader behavior") {
  SUBCASE("Provides instructions from file") {
    Instruction expectedInstructions[] = {
        {OpCode::Push, 2}, {OpCode::Push, 3}, {OpCode::Add}};

    TestMuFile testFile("test.mu", expectedInstructions);

    Loader muFile("test.mu");

    VerifyInstructions(expectedInstructions, muFile.GetInstructions());
  }
}

