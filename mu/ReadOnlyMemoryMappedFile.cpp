#include "Configuration.hpp"

#include "ReadOnlyMemoryMappedFile.hpp"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

ReadOnlyMemoryMappedFile::ReadOnlyMemoryMappedFile(const char* filePath)
    : m_fileSize(0), m_fileHandle(-1), m_fileBuffer(nullptr) {
  struct stat st;
  // The stat function returns zero if the file exists.
  if (stat(filePath, &st) == 0) {
    m_fileSize = st.st_size;

    m_fileHandle = open(filePath, O_RDONLY, 0);
    m_fileBuffer = (byte*)mmap(0, m_fileSize, PROT_READ, MAP_FILE | MAP_PRIVATE,
                               m_fileHandle, 0);
  }
}

ReadOnlyMemoryMappedFile::~ReadOnlyMemoryMappedFile() {
  if (m_fileBuffer != nullptr)
    munmap(m_fileBuffer, m_fileSize);
  if (m_fileHandle != -1)
    close(m_fileHandle);
}

byte* ReadOnlyMemoryMappedFile::GetBuffer() { return m_fileBuffer; }

size_t ReadOnlyMemoryMappedFile::GetSize() { return m_fileSize; }

TEST_CASE("Verify read-only memory mapped file behavior") {
  SUBCASE("File that does not exist has zero size and a nullptr buffer") {
    ReadOnlyMemoryMappedFile doesNotExist("NoFile");
    CHECK(doesNotExist.GetSize() == 0);
    CHECK(doesNotExist.GetBuffer() == nullptr);
  }

  SUBCASE("File is loaded with proper size and data") {
    // This is pretty ugly - there is no literal for std::byte, so we need to
    // explicitly convert each array argument.
    byte expectedData[] = {byte{1}, byte{2}, byte{3}, byte{4}};
    TestFile testFile("test.data", expectedData, sizeof(expectedData));

    ReadOnlyMemoryMappedFile memoryMappedFile("test.data");

    REQUIRE(memoryMappedFile.GetSize() == 4);

    byte* actualData = memoryMappedFile.GetBuffer();
    REQUIRE(expectedData[0] == actualData[0]);
    REQUIRE(expectedData[1] == actualData[1]);
    REQUIRE(expectedData[2] == actualData[2]);
    REQUIRE(expectedData[3] == actualData[3]);
  }
}
