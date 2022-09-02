#pragma once

#include <cassert>

#include "ValueStack.hpp"

template <typename OperationCallback>
void PerformBinaryOperation(OperationCallback&& op) {
  assert(StackSize() >= 2);

  auto right = Pop();
  auto left = Pop();

  if (left.Type() == ArgumentType::i64 && right.Type() == ArgumentType::i64)
    Push(op(left.i64(), right.i64()));
  else if (left.Type() == ArgumentType::i32 &&
           right.Type() == ArgumentType::i32)
    Push(op(left.i32(), right.i32()));
  else if (left.Type() == ArgumentType::i64 &&
           right.Type() == ArgumentType::i32)
    Push(op(left.i64(), right.i32()));
  else if (left.Type() == ArgumentType::i32 &&
           right.Type() == ArgumentType::i64)
    Push(op(left.i32(), right.i64()));
  else
    assert(0 && "Missing binary arithmetic operation case");
}
