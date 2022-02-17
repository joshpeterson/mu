#pragma once

#include "Bytecode.hpp"

auto Push(i64 value) -> void;
auto Pop() -> i64;
auto StackSize() -> int;
