#define DOCTEST_CONFIG_IMPLEMENT
#include "external/doctest/doctest.h"

#include <fmt/core.h>
using fmt::print;

#include "mu/Bytecode.hpp"
#include "mu/InstructionProcessor.hpp"
#include "mu/Loader.hpp"
#include "mu/Mutext/Parser.hpp"

// This is temporary until we have a ret opcode.
#include "mu/Log.hpp"
#include "mu/ValueStack.hpp"

int PrintHelp();
int RunTests(int argc, char* argv[]);
int ProcessMutextFile(const char* muFilePath);
int ProcessBytecodeFile(const char* muFilePath);

bool AreEqual(const char* left, const char* right);
bool StartsWith(const char* haystack, const char* needle);
bool IsMutextFile(const char* filePath);

int main(int argc, char** argv) {
  InitializeInstructions();
  if (argc != 2 || AreEqual(argv[1], "--help")) {
    return PrintHelp();
  } else if (AreEqual(argv[1], "--test") ||
             AreEqual(argv[1], "--list-test-cases") ||
             StartsWith(argv[1], "--test-case")) {
    return RunTests(argc, argv);
  } else if (IsMutextFile(argv[1])) {
    return ProcessMutextFile(argv[1]);
  } else {
    return ProcessBytecodeFile(argv[1]);
  }
}

int PrintHelp() {
  print("===========================================================\n");
  print("Welcome to the \u03BC VM!\n");
  print("\n");
  print("Usage: mu <options | file.mu | file.mut>\n");
  print("  - file.mu is a binary \u03BC bytecode file.\n");
  print("  - file.mut is a text \u03BCtext file.\n");
  print("\n");
  print("Options:\n");
  print("  --help - Display this message.\n");
  print("  --test - Run \u03BC's tests (if provided, file.mu is ignored).\n");
  print("\n");
  print("Note that file.mu should be a \u03BC bytecode file to execute.\n");
  print("===========================================================\n");

  return 0;
}

int RunTests(int argc, char* argv[]) {
  doctest::Context context;

  context.setOption("no-intro", true);
  context.setOption("no-version", true);
  context.setOption("exit", true);

  context.applyCommandLine(argc, argv);

  int res = context.run();

  if (context.shouldExit())
    return res;
  return 1;
}

int ProcessMutextFile(const char* muFilePath) {
  auto instructions = ParseMutextFile(muFilePath);
  Process(instructions);
  // This is temporary until we have a ret opcode.
  if (StackSize() > 0)
    Log("Top value: {}", Pop());
  return 0;
}

int ProcessBytecodeFile(const char* muFilePath) {
  Loader loader(muFilePath);
  if (loader.GetInstructions().size() == 0) {
    print("Error: {}\n", loader.GetErrorMessage());
    return 1;
  }

  Process(loader.GetInstructions());
  return 0;
}

bool AreEqual(const char* left, const char* right) {
  return strcmp(left, right) == 0;
}

bool StartsWith(const char* haystack, const char* needle) {
  return strncmp(needle, haystack, strlen(needle)) == 0;
}

bool IsMutextFile(const char* filePath) {
  return string(filePath).ends_with(".mut");
}
