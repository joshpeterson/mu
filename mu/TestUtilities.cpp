#include <doctest.h>

#include <cstdio>
#include <cstring>

#include <fmt/core.h>
using fmt::format;

#include "TestUtilities.hpp"

#include "Loader.hpp"

TestFile::TestFile(const char* testFilePath, byte* data, size_t numberOfBytes)
    : m_testFilePath(testFilePath) {
  auto testFileHandle = fopen(m_testFilePath, "wb");
  fwrite(data, 1, numberOfBytes, testFileHandle);
  fclose(testFileHandle);
}

TestFile::~TestFile() { std::remove(m_testFilePath); }

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

size_t TestMuFile::GetMuFileSize(span<Instruction> instructions) {
  return sizeof(Loader::MuMagicHeader) + instructions.size_bytes();
}

void VerifyInstructions(span<Instruction> expected, span<Instruction> actual) {
  REQUIRE(expected.size() == actual.size());

  for (auto i = 0; i < expected.size(); i++) {
    REQUIRE(expected[i] == actual[i]);
  }
}

doctest::String toString(const Instruction& instruction) {
  return format("OpCode: {} Argument: {}", instruction.opCode,
                instruction.argument)
      .c_str();
}
