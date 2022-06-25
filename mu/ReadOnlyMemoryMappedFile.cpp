#include "ReadOnlyMemoryMappedFile.hpp"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

ReadOnlyMemoryMappedFile::ReadOnlyMemoryMappedFile(const char* filePath) {
  struct stat st;
  stat(filePath, &st);
  m_fileSize = st.st_size;

  m_fileHandle = open(filePath, O_RDONLY, 0);
  m_fileBuffer = (byte*)mmap(0, m_fileSize, PROT_READ, MAP_FILE | MAP_PRIVATE,
                             m_fileHandle, 0);
}

ReadOnlyMemoryMappedFile::~ReadOnlyMemoryMappedFile() {
  munmap(m_fileBuffer, m_fileSize);
  close(m_fileHandle);
}

byte* ReadOnlyMemoryMappedFile::GetBuffer() { return m_fileBuffer; }

size_t ReadOnlyMemoryMappedFile::GetSize() { return m_fileSize; }

