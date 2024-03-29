#include "Configuration.hpp"

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

Stack valueStack;

TEST_CASE("Verify value stack behavior") {
  SUBCASE("Can push and pop") {
    Push(42);
    CHECK(Pop().i32() == 42);

    Push(43);
    CHECK(Pop().i32() == 43);
  }

  SUBCASE("Can allocate more than 20 values") {
    int i = 0;
    for (; i < 100; i++) {
      Push(i);
    }
    CHECK(Pop().i32() == i - 1);
  }
}
