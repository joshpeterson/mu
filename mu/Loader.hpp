#pragma once

#include <span>
using std::span;
#include <string>
using std::string;

#include "Bytecode.hpp"
#include "ReadOnlyMemoryMappedFile.hpp"

///
/// @brief A Loader is used to open a binary mu file.
///
/// Instructions can be loaded from a binary file. This type opens that file
/// and provides a list of instructions to be executed. It closes the file
/// when the instance of the Loader goes out of scope.
///
class Loader {
public:
  Loader(const char* muFilePath);

  span<Instruction> GetInstructions() const;
  string GetErrorMessage() const;

  ///
  /// @MuMagicHeader An 8 byte value that must be at the start of a valid mu
  /// file.
  ///
  static const uint64_t MuMagicHeader = 0xDAFFDAFF;

private:
  const char* m_muFilePath;
  ReadOnlyMemoryMappedFile m_muFile;
  span<Instruction> m_instructions;

  enum class ErrorCondition { NoError, FileDoesNotExist, InvalidHeader };
  ErrorCondition m_errorCondition;
};
