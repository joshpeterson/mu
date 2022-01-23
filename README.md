# μ Virtual Machine

The μ VM is a tiny stack based virtual machine designed for fun and learning. It has the
following parts:

* A [bytecode](mu/Bytecode.hpp) that define its operations
* A [value stack](mu/ValueStack.cpp) to store the values those instructions operate on
* An [interpreter](mu/Interpreter.cpp) that executes each instruction as a C++ function
* An [instruction processor](mu/InstructionProcessor.cpp) that executes instructions

Tests for each part of the VM are written immediately after the part they test.
