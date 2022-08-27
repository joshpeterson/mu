#pragma once

// == Interpreter ==
//
// The intrepreter provides an implementation for each instruction the VM can
// execute. Each instruction implementation is responsible to operating on the
// value stack properly.

#include "Interpreter/Add.hpp"
#include "Interpreter/Subtract.hpp"
