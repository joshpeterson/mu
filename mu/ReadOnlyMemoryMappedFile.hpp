#pragma once

#include <cstddef>
using std::byte;

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

