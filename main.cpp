#define DOCTEST_CONFIG_IMPLEMENT
#include "external/doctest/doctest.h"

#include <fmt/core.h>
using fmt::print;

#include "mu/InstructionProcessor.hpp"
#include "mu/Loader.hpp"

int PrintHelp();
int RunTests(int argc, char* argv[]);
int ProcessBytecodeFile(const char* muFilePath);

bool AreEqual(const char* left, const char* right);

int main(int argc, char** argv) {
  if (argc != 2 || AreEqual(argv[1], "--help")) {
    return PrintHelp();
  } else if (AreEqual(argv[1], "--test")) {
    return RunTests(argc, argv);
  } else {
    return ProcessBytecodeFile(argv[1]);
  }
}

int PrintHelp() {
  print("===========================================================\n");
  print("Welcome to the \u03BC VM!\n");
  print("\n");
  print("Usage: mu <options | file.mu>\n");
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
