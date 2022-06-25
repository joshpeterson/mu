#pragma once

#if MU_TESTING_ENABLED

#include <span>
using std::span;

#include "Bytecode.hpp"

class TestMuFile {
public:
  TestMuFile(const char* testFilePath, span<Instruction> instructions);
  ~TestMuFile();

private:
  const char* m_testFilePath;
};

#endif // MU_TESTING_ENABLED
