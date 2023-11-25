#include "Configuration.hpp"

#include <cstdio>
#include <cstring>

#include <fmt/core.h>
using fmt::format;

#include "TestUtilities.hpp"

#include "Loader.hpp"

///
/// @brief Create a new instance of a TestFile object.
///
/// @param[in] testFilePath The absolute path to the file to be created.
/// @param[in] data The data to write to the file.
///
TestFile::TestFile(const char* testFilePath, const char* data)
    : TestFile(testFilePath, reinterpret_cast<const byte*>(data),
               strlen(data)) {}

TestFile::TestFile(const char* testFilePath, const byte* data,
                   size_t numberOfBytes)
    : m_testFilePath(testFilePath) {
  auto testFileHandle = fopen(m_testFilePath, "wb");
  fwrite(data, 1, numberOfBytes, testFileHandle);
  fclose(testFileHandle);
}

///
/// @brief Delete the file that was created in the constructor.
///
///
TestFile::~TestFile() { std::remove(m_testFilePath); }

///
/// @brief Create a new instance of a TestMuFile object.
///
/// @param[in] testFilePath The absolute path to the file to be created.
/// @param[in] instructions The instructions to write to the file.
///
TestMuFile::TestMuFile(const char* testFilePath, span<Instruction> instructions)
    : m_testFile(testFilePath, (byte*)GetMuFileData(instructions),
                 GetMuFileSize(instructions)) {}
TestMuFile::~TestMuFile() { free(m_MuFileBuffer); }

byte* TestMuFile::GetMuFileData(span<Instruction> instructions) {
  m_MuFileBuffer =
      (byte*)malloc(sizeof(Loader::MuMagicHeader) + instructions.size_bytes());
  auto magicHeader = Loader::MuMagicHeader;
  memcpy(m_MuFileBuffer, &magicHeader, sizeof(magicHeader));
  memcpy(m_MuFileBuffer + sizeof(Loader::MuMagicHeader), instructions.data(),
         instructions.size_bytes());
  return m_MuFileBuffer;
}

///
/// @brief Determine the size of the mu binary file with the given instructions.
///
/// @param[in] instructions The instructions to write to the file.
/// @return The number of bytes the my binary files will require.
///
size_t TestMuFile::GetMuFileSize(span<Instruction> instructions) {
  return sizeof(Loader::MuMagicHeader) + instructions.size_bytes();
}

///
/// @brief Verify that the expected instructions are the same as the actual.
///
/// @param[in] expected The expected instructions.
/// @param[in] actual The actual instructions.
///
void VerifyInstructions(span<Instruction> expected, span<Instruction> actual) {
  REQUIRE(expected.size() == actual.size());

  for (auto i = 0; i < expected.size(); i++) {
    REQUIRE(expected[i] == actual[i]);
  }
}

// This helper function is used to display a given instuction as a string in the
// test output.

///
/// @brief A helper function to display a given instruction as a string for the
/// doctest library.
///
/// @param[in] instruction The instruction to convert to a string.
/// @return The string representation of the instruction.
///
doctest::String toString(const Instruction& instruction) {
  return format("OpCode: {} Argument: {}", instruction.opCode,
                instruction.argument)
      .c_str();
}
