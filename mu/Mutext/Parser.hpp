#pragma once

#include <vector>
using std::vector;

#include "Bytecode.hpp"

// Public API
vector<Instruction> ParseMutextFile(const char* mutextFilePath);

// Internal API
static string GetFileContents(const char* filename);
static vector<Instruction> Parse(const char* mutextFileData);
static vector<string> SplitStringIntoLines(const string& input);
static Instruction ParseLine(string line);
static bool IsWhiteSpace(const string& line);
static Argument ParseArgument(string line);
static ArgumentType FromString(string typeString);
static Argument OfType(ArgumentType argumentType, auto value);
