#include "TestUtilities.hpp"
#include <doctest.h>

#include <cstddef>
using std::byte;

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "Loader.hpp"

auto Load(const char* muFilePath) -> span<Instruction> {
  struct stat st;
  stat(muFilePath, &st);
  size_t fileSize = st.st_size;

  int muFileHandle = open(muFilePath, O_RDONLY, 0);
  byte* muFileBuffer = (byte*)mmap(0, fileSize, PROT_READ,
                                   MAP_FILE | MAP_PRIVATE, muFileHandle, 0);

  Instruction* instructions = (Instruction*)muFileBuffer;
  size_t numberOfInstructions = fileSize / sizeof(Instruction);
  return span<Instruction>{instructions, numberOfInstructions};
}

TEST_CASE("Verify loader behavior") {
  SUBCASE("Returns instruction from file") {
    Instruction expectedInstructions[] = {
        {OpCode::Push, 2}, {OpCode::Push, 3}, {OpCode::Add}};
    TestMuFile testFile("test.mu", expectedInstructions);

    auto actualInstructions = Load("test.mu");

    VerifyInstructions(expectedInstructions, actualInstructions);
  }
}

