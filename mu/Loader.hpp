#pragma once

#include <span>
using std::span;
#include <string>
using std::string;

#include "Bytecode.hpp"
#include "ReadOnlyMemoryMappedFile.hpp"

class Loader {
public:
  Loader(const char* muFilePath);

  span<Instruction> GetInstructions() const;
  string GetErrorMessage() const;

private:
  const char* m_muFilePath;
  ReadOnlyMemoryMappedFile m_muFile;
  span<Instruction> m_instructions;

  enum class ErrorCondition { NoError, FileDoesNotExist };
  ErrorCondition m_errorCondition;
};
