#include <doctest.h>

#include <stack>
using std::stack;

#include "ValueStack.hpp"

// == Value Stack ==
//
// Each instruction operates on the value stack, poping values from the stack as
// it needs them and pushing results on to the stack. The value stack is free to
// grow and shrink as necessary to execute the instructions.

// Here `static` means that the `valueStack` obect is only visible in this file.
// It is an implementation detail that we don't want to leak to any other code.
// Other code should only use the "Value Stack" based its public API (i.e. its
// methods).
static stack<int64_t> valueStack;

void Push(int64_t value) { valueStack.push(value); }

int64_t Pop() {
  auto value = valueStack.top();
  valueStack.pop();
  return value;
}

int StackSize() { return valueStack.size(); }

TEST_CASE("Verify value stack behavior") {
  Push(42);
  CHECK(Pop() == 42);

  Push(43);
  CHECK(Pop() == 43);
}
