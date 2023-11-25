#pragma once

#include <cstddef>
using std::byte;

///
/// @brief Open a read-only memory mapped file, and close it when an instance of
/// this type goes out of scope.
///
class ReadOnlyMemoryMappedFile {
public:
  ReadOnlyMemoryMappedFile(const char* filePath);
  ~ReadOnlyMemoryMappedFile();

  byte* GetBuffer();
  size_t GetSize();

private:
  int m_fileHandle;
  byte* m_fileBuffer;
  size_t m_fileSize;
};
