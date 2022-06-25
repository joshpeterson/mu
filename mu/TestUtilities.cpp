#if MU_TESTING_ENABLED

#include <cstdio>

#include "TestUtilities.hpp"

TestMuFile::TestMuFile(const char* testFilePath, span<Instruction> instructions)
    : m_testFilePath(testFilePath) {
  auto testFileHandle = fopen(m_testFilePath, "wb");
  fwrite(instructions.data(), 1, instructions.size_bytes(), testFileHandle);
  fclose(testFileHandle);
}

TestMuFile::~TestMuFile() { std::remove(m_testFilePath); }

#endif // MU_TESTING_ENABLED
