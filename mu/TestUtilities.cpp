#if MU_TESTING_ENABLED
#include <doctest.h>

#include <cstdio>

#include "TestUtilities.hpp"

TestFile::TestFile(const char* testFilePath, byte* data, size_t numberofBytes)
    : m_testFilePath(testFilePath) {
  auto testFileHandle = fopen(m_testFilePath, "wb");
  fwrite(data, 1, numberofBytes, testFileHandle);
  fclose(testFileHandle);
}

TestFile::~TestFile() { std::remove(m_testFilePath); }

TestMuFile::TestMuFile(const char* testFilePath, span<Instruction> instructions)
    : m_testFile(testFilePath, (byte*)instructions.data(),
                 instructions.size_bytes()) {}

void VerifyInstructions(span<Instruction> expected, span<Instruction> actual) {
  REQUIRE(expected.size() == actual.size());

  for (auto i = 0; i < expected.size(); i++) {
    REQUIRE(expected[i] == actual[i]);
  }
}

#endif // MU_TESTING_ENABLED
