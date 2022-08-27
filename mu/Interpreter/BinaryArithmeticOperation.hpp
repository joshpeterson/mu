#pragma once

#include <cstdint>

// Binary arithmetic operations will all need to load instructions from the
// value stack in the same way. This define hides a bit of ugliness in C++,
// which does not allow function pointers to be defined from generic functions,
// but can allow one generic lambda to be used for multiple arguments. This
// means we cannot have just one argument to the implementation of the function
// which pulls values from the stack with the proper types. Instead, we hide
// that complexity with this macro.
#define PerformBinaryOperation(op) PerformBinaryOperationImpl(op, op, op, op)

typedef int32_t (*Operation3232)(int32_t, int32_t);
typedef int64_t (*Operation3264)(int32_t, int64_t);
typedef int64_t (*Operation6432)(int64_t, int32_t);
typedef int64_t (*Operation6464)(int64_t, int64_t);

void PerformBinaryOperationImpl(Operation3232 op3232, Operation3264 op3264,
                                Operation6432 op6432, Operation6464 op6464);