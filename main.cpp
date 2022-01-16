#define DOCTEST_CONFIG_IMPLEMENT
#include "external/doctest/doctest.h"

int main(int argc, char** argv) {
  doctest::Context context;

  context.setOption("no-intro", true);
  context.setOption("no-version", true);
  context.setOption("exit", true);

  context.applyCommandLine(argc, argv);

  int res = context.run();

  if (context.shouldExit())
    return res;

  printf("Here\n");

  return 0;
}
