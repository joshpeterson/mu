#if MU_TESTING_ENABLED
#include <doctest.h>

#include <cstdio>

#include "TestUtilities.hpp"

TestMuFile::TestMuFile(const char* testFilePath, span<Instruction> instructions)
    : m_testFilePath(testFilePath) {
  auto testFileHandle = fopen(m_testFilePath, "wb");
  fwrite(instructions.data(), 1, instructions.size_bytes(), testFileHandle);
  fclose(testFileHandle);
}

TestMuFile::~TestMuFile() { std::remove(m_testFilePath); }

void VerifyInstructions(span<Instruction> expected, span<Instruction> actual) {
  CHECK(expected.size() == actual.size());

  for (auto i = 0; i < expected.size(); i++) {
    CHECK(expected[i] == actual[i]);
  }
}

#endif // MU_TESTING_ENABLED
