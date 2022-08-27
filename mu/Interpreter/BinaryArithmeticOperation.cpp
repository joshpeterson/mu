#include <cassert>

#include "Interpreter/BinaryArithmeticOperation.hpp"
#include "ValueStack.hpp"

void PerformBinaryOperationImpl(Operation3232 op3232, Operation3264 op3264,
                                Operation6432 op6432, Operation6464 op6464) {
  assert(StackSize() >= 2);

  auto right = Pop();
  auto left = Pop();

  if (left.Type() == ArgumentType::i64 && right.Type() == ArgumentType::i64)
    Push(op6464(left.i64(), right.i64()));
  else if (left.Type() == ArgumentType::i64 &&
           right.Type() == ArgumentType::i32)
    Push(op6432(left.i64(), right.i32()));
  else if (left.Type() == ArgumentType::i32 &&
           right.Type() == ArgumentType::i64)
    Push(op3264(left.i32(), right.i64()));
  else
    Push(op3232(left.i32(), right.i32()));
}