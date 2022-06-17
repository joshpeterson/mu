#pragma once

#include <span>
using std::span;

#include "Bytecode.hpp"

auto Load(const char* muFilePath) -> span<Instruction>;
