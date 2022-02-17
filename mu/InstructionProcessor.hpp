#pragma once

#include <span>
using std::span;

#include "Bytecode.hpp"

auto Process(span<Instruction> instructions) -> void;
