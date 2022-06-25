#pragma once

#include <span>
using std::span;

#include "Bytecode.hpp"
#include "ReadOnlyMemoryMappedFile.hpp"

class Loader {
public:
  Loader(const char* muFilePath);

  span<Instruction> GetInstructions() const;

private:
  ReadOnlyMemoryMappedFile m_muFile;
  span<Instruction> m_instructions;
};
