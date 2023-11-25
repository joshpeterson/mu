#pragma once

#include "Configuration.hpp"

#include <cstddef>
using std::byte;
#include <span>
using std::span;

#include "Bytecode.hpp"

///
/// @brief Write a file at a given path, with the given data, then delete it
/// when the instance of this type goes out of scope.
///
class TestFile {
public:
  TestFile(const char* testFilePath, const char* data);
  TestFile(const char* testFilePath, const byte* data, size_t numberOfBytes);
  ~TestFile();

private:
  const char* m_testFilePath;
};

///
/// @brief Write a mu binary file at a given path, with the given instructions,
/// and delete it when the instance of this type goes out of scope.
///
class TestMuFile {
public:
  TestMuFile(const char* testFilePath, span<Instruction> instructions);
  ~TestMuFile();

private:
  TestFile m_testFile;
  byte* m_MuFileBuffer;

  byte* GetMuFileData(span<Instruction> instructions);
  size_t GetMuFileSize(span<Instruction> instructions);
};

void VerifyInstructions(span<Instruction> expected, span<Instruction> actual);

doctest::String toString(const Instruction& value);
