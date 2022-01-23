#pragma once

#include <span>
using std::span;

#include "Bytecode.hpp"

void Process(span<Instruction> instructions);
