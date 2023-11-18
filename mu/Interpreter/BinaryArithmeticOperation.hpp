#pragma once

#include <cassert>

#include "ValueStack.hpp"

///
/// @brief Perform a binary arithmetic operation.
/// This function handles the common logic for performing a binary
/// arithmetic operation. It pops two values from the value stack, performs the
/// operation, and pushes the result back onto the value stack. It ensure that
/// argument types are access properly from the Arguments on the stack.
/// Call it with a generic lambda that takes two arguments and returns a value.
///
/// @tparam OperationCallback The type of the operation callback. This is not
/// used, allow the compiler to determine it from the generic lambda passed to
/// this function.
/// @param[in] op The binary options to perform.
///
template <typename OperationCallback>
void PerformBinaryOperation(OperationCallback&& op) {
  assert(StackSize() >= 2);

  auto right = Pop();
  auto left = Pop();

  if (left.Type() == ArgumentType::i32) {
    if (right.Type() == ArgumentType::i32)
      Push(op(left.i32(), right.i32()));
    else if (right.Type() == ArgumentType::i64)
      Push(op(left.i32(), right.i64()));
    else if (right.Type() == ArgumentType::f32)
      Push(op(left.i32(), right.f32()));
    else if (right.Type() == ArgumentType::f64)
      Push(op(left.i32(), right.f64()));
  } else if (left.Type() == ArgumentType::i64) {
    if (right.Type() == ArgumentType::i64)
      Push(op(left.i64(), right.i64()));
    else if (right.Type() == ArgumentType::i32)
      Push(op(left.i64(), right.i32()));
    else if (right.Type() == ArgumentType::f32)
      Push(op(left.i64(), right.f32()));
    else if (right.Type() == ArgumentType::f64)
      Push(op(left.i64(), right.f64()));
  } else if (left.Type() == ArgumentType::f32) {
    if (right.Type() == ArgumentType::f32)
      Push(op(left.f32(), right.f32()));
    else if (right.Type() == ArgumentType::i32)
      Push(op(left.f32(), right.i32()));
    else if (right.Type() == ArgumentType::i64)
      Push(op(left.f32(), right.i64()));
    else if (right.Type() == ArgumentType::f64)
      Push(op(left.f32(), right.f64()));
  } else if (left.Type() == ArgumentType::f64) {
    if (right.Type() == ArgumentType::f64)
      Push(op(left.f64(), right.f64()));
    else if (right.Type() == ArgumentType::i32)
      Push(op(left.f64(), right.i32()));
    else if (right.Type() == ArgumentType::i64)
      Push(op(left.f64(), right.i64()));
    else if (right.Type() == ArgumentType::f32)
      Push(op(left.f64(), right.f32()));
  } else
    assert(0 && "Missing binary arithmetic operation case");
}
