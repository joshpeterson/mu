#pragma once

#if MU_TESTING_ENABLED

#include <cstddef>
using std::byte;
#include <span>
using std::span;

#include "Bytecode.hpp"

class TestFile {
public:
  TestFile(const char* testFilePath, byte* data, size_t numberofBytes);
  ~TestFile();

private:
  const char* m_testFilePath;
};

class TestMuFile {
public:
  TestMuFile(const char* testFilePath, span<Instruction> instructions);

private:
  TestFile m_testFile;
};

void VerifyInstructions(span<Instruction> expected, span<Instruction> actual);

#endif // MU_TESTING_ENABLED
