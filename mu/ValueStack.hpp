#pragma once

#include <cstdlib>
using std::malloc;
using std::realloc;

#include "Bytecode.hpp"

struct Stack {
public:
  Stack() : currentIndex(-1), reservedNumberOfEntries(20) {
    values = (Argument*)malloc(reservedNumberOfEntries * sizeof(Argument));
  }

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

  constexpr void pop() {
    assert(currentIndex >= 0);
    currentIndex--;
  }

  constexpr Argument top() { return values[currentIndex]; }

  constexpr int size() { return currentIndex + 1; }

private:
  Argument* values;
  int currentIndex;
  int reservedNumberOfEntries;
};

extern Stack valueStack;

constexpr inline void Push(Argument value) { valueStack.push(value); }

constexpr inline Argument Pop() {
  auto value = valueStack.top();
  valueStack.pop();
  return value;
}

constexpr inline int StackSize() { return valueStack.size(); }
