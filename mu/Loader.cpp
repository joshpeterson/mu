#include "TestUtilities.hpp"
#include <doctest.h>

#include <fmt/core.h>
using fmt::format;

#include "Loader.hpp"

// == Loader ==
//
// Instructions can be loaded from a binary file. This class opens that file
// and provides a list of instructions to be executed. It closes the file
// when the instance of the Loadrer does out of scope.

Loader::Loader(const char* muFilePath)
    : m_muFilePath(muFilePath), m_muFile(muFilePath),
      m_errorCondition(ErrorCondition::NoError) {
  auto fileData = m_muFile.GetBuffer();
  if (fileData == nullptr) {
    m_errorCondition = ErrorCondition::FileDoesNotExist;
  } else if (*(uint32_t*)fileData != MuMagicHeader) {
    m_errorCondition = ErrorCondition::InvalidHeader;
  } else {

    auto instructionBuffer = (Instruction*)(fileData + sizeof(MuMagicHeader));
    auto numberOfInstructions = m_muFile.GetSize() / sizeof(Instruction);
    m_instructions = span<Instruction>{instructionBuffer, numberOfInstructions};
  }
}

span<Instruction> Loader::GetInstructions() const { return m_instructions; }

string Loader::GetErrorMessage() const {
  if (m_errorCondition == ErrorCondition::FileDoesNotExist)
    return format("The file '{}' does not exist.", m_muFilePath);
  if (m_errorCondition == ErrorCondition::InvalidHeader)
    return format("The file '{}' is not a valid Mu file.", m_muFilePath);
  return "";
}

TEST_CASE("Verify loader behavior") {
  SUBCASE("Provides instructions from file") {
    Instruction expectedInstructions[] = {
        {OpCode::Push, 2}, {OpCode::Push, 3}, {OpCode::Add}};

    TestMuFile testFile("test.mu", expectedInstructions);

    Loader muFile("test.mu");

    VerifyInstructions(expectedInstructions, muFile.GetInstructions());
  }

  SUBCASE("When file does not exist, provides no instructions ") {
    Loader muFileThatDoesNotExist("nofile.mu");
    REQUIRE(muFileThatDoesNotExist.GetInstructions().size() == 0);
  }

  SUBCASE("When file does not exist, provides useful error message ") {
    Loader muFileThatDoesNotExist("nofile.mu");
    REQUIRE(muFileThatDoesNotExist.GetErrorMessage() ==
            "The file 'nofile.mu' does not exist.");
  }

  SUBCASE(
      "When the file is loaded correctly, provides an empty error message") {
    Instruction expectedInstructions[] = {
        {OpCode::Push, 2}, {OpCode::Push, 3}, {OpCode::Add}};

    TestMuFile testFile("test.mu", expectedInstructions);

    Loader muFile("test.mu");

    REQUIRE(muFile.GetErrorMessage() == "");
  }

  SUBCASE(
      "When a file is not a valid .mu file, provides useful error message ") {
    int invalidMuFileData[] = {1, 2};
    TestFile testFile("invalidMuFile.mu", (byte*)invalidMuFileData,
                      sizeof(invalidMuFileData));

    Loader muFile("invalidMuFile.mu");

    REQUIRE(muFile.GetErrorMessage() ==
            "The file 'invalidMuFile.mu' is not a valid Mu file.");
  }
}

