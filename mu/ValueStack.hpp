#pragma once

#include <cstdlib>
using std::malloc;
using std::realloc;

#include "Bytecode.hpp"

///
/// @brief A stack implementation used to store Argument instances. The stack
/// will allocate more member when more entries must be stored, but it will not
/// free that memory if the stack shrinks.
///
class Stack {
public:
  ///
  /// @brief Create a new stack, with space for 20 Arguments by default.
  ///
  Stack() : currentIndex(-1), reservedNumberOfEntries(20) {
    values = (Argument*)malloc(reservedNumberOfEntries * sizeof(Argument));
  }

  ///
  /// @brief Push an Argument on to the stack.
  ///
  /// @param[in] value The Argument to push on to the stack.
  ///
  constexpr void push(Argument value) {
    currentIndex++;
    if (currentIndex >= reservedNumberOfEntries) {
      reservedNumberOfEntries *= 2;
      values = (Argument*)realloc(values,
                                  reservedNumberOfEntries * sizeof(Argument));
    }
    assert(currentIndex < reservedNumberOfEntries);
    values[currentIndex] = value;
  }

  ///
  /// @brief Pop an Argument off of the stack.
  ///
  ///
  constexpr void pop() {
    assert(currentIndex >= 0);
    currentIndex--;
  }

  ///
  /// @brief Return the Argument at the top of the stack.
  ///
  /// @return The Argument at the top of the stack.
  ///
  constexpr Argument top() { return values[currentIndex]; }

  ///
  /// @brief Find the number of Arguments on the stack.
  ///
  /// @return The number of Arguments on the stack.
  ///
  constexpr int size() { return currentIndex + 1; }

private:
  Argument* values;
  int currentIndex;
  int reservedNumberOfEntries;
};

///
/// @brief A global instance of the stack used to store Argument instances.
///
extern Stack valueStack;

///
/// @brief Push an Argument on to the value stack.
///
/// @param[in] value The Argument to push on to the stack.
///
constexpr inline void Push(Argument value) { valueStack.push(value); }

///
/// @brief Pop an Argument off of the value stack and return it.
///
/// @return The Argument that was popped off of the stack.
///
constexpr inline Argument Pop() {
  auto value = valueStack.top();
  valueStack.pop();
  return value;
}

///
/// @brief Get the number of Arguments on the value stack.
///
/// @return The number of Arguments on the value stack.
///
constexpr inline int StackSize() { return valueStack.size(); }
