#include "Configuration.hpp"

#include <algorithm>
using std::all_of;

#include <charconv>
using std::from_chars;

#include <string>
using std::string;

#include "Bytecode.hpp"
#include "Parser.hpp"
#include "StringUtils.hpp"

///
/// @brief Convert a text file with mu instructions into a list of Instructions.
///
/// @param[in] mutextFilePath The path to the mu text fike to parse.
///
vector<Instruction> ParseMutextFile(const char* mutextFilePath) {
  return Parse(GetFileContents(mutextFilePath).c_str());
}

TEST_CASE("Verify ParseMutextFile behavior") {
  SUBCASE("Returns no instructions when given an empty file path") {
    auto instructions = ParseMutextFile("");
    CHECK(instructions.empty());
  }

  SUBCASE(
      "Returns no instructions when given a file path that does not exist") {
    auto instructions = ParseMutextFile("does_not_exist.txt");
    CHECK(instructions.empty());
  }

  SUBCASE("Can parse multiple instructions from a file") {
    TestFile testFile("test.mut", "Pop\nPush i32:42\n");
    auto instructions = ParseMutextFile("test.mut");
    CHECK(instructions.size() == 2);
    CHECK(instructions[0].opCode == OpCode::Pop);
    CHECK(instructions[1].opCode == OpCode::Push);
    CHECK(instructions[1].argument.Type() == ArgumentType::i32);
    CHECK(instructions[1].argument.i32() == 42);
  }
}

///
/// @brief Read the contents of a file into a string.
///
/// @param[in] filename The path to the file.
/// @return string The contents of the file.
///
static string GetFileContents(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if (file == nullptr)
    return "";

  fseek(file, 0, SEEK_END);
  const size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  string contents;
  contents.resize(size);
  fread(contents.data(), 1, size, file);
  fclose(file);

  return contents;
}

///
/// @brief Process a mu text file, parsing it into Instructions.
///
/// @param[in] mutextFileData The path to the text file to parse.
///
static vector<Instruction> Parse(const char* mutextFileData) {
  auto lines = SplitStringIntoLines(mutextFileData);
  vector<Instruction> instructions;
  for (auto& line : lines) {
    instructions.push_back(ParseLine(line));
  }
  return instructions;
}

TEST_CASE("Verify Parse behavior") {
  SUBCASE("Can parse an empty file") {
    auto instructions = Parse("");
    CHECK(instructions.size() == 0);
  }

  SUBCASE("Can parse a single instruction") {
    auto instructions = Parse("Pop\n");
    CHECK(instructions.size() == 1);
    CHECK(instructions[0].opCode == OpCode::Pop);
  }

  SUBCASE("Can parse a single instruction with a parameter") {
    auto instructions = Parse("Add\n");
    CHECK(instructions.size() == 1);
    CHECK(instructions[0].opCode == OpCode::Add);
  }

  SUBCASE("Can parse a single Push instruction with a parameter") {
    auto instructions = Parse("Push i32:42\n");
    CHECK(instructions.size() == 1);
    CHECK(instructions[0].opCode == OpCode::Push);
    CHECK(instructions[0].argument.Type() == ArgumentType::i32);
    CHECK(instructions[0].argument.i32() == 42);
  }

  SUBCASE("Can parse two instructions") {
    auto instructions = Parse("Pop\nPush i32:42\n");
    CHECK(instructions.size() == 2);
    CHECK(instructions[0].opCode == OpCode::Pop);
    CHECK(instructions[1].opCode == OpCode::Push);
    CHECK(instructions[1].argument.Type() == ArgumentType::i32);
    CHECK(instructions[1].argument.i32() == 42);
  }
}

///
/// @brief Split a single string into multiple strings on line breaks.
///
/// @param[in] input the string to split.
/// @return vector<string> One string per line of the input.
///
vector<string> SplitStringIntoLines(const string& input) {
  vector<string> lines;
  string::size_type pos = 0;
  string::size_type prev = 0;

  while ((pos = input.find("\n", prev)) != string::npos) {
    auto line = input.substr(prev, pos - prev);
    if (!IsWhiteSpace(line)) {
      lines.push_back(line);
      prev = pos + 1;
    }
  }

  auto last_line = input.substr(prev);
  if (!IsWhiteSpace(last_line))
    lines.push_back(last_line);

  return lines;
}

TEST_CASE("Verify SplitStringIntoLines behavior") {
  SUBCASE("Can split a string into lines") {
    auto lines = SplitStringIntoLines("Hello\nWorld");
    CHECK(lines.size() == 2);
    CHECK(lines[0] == "Hello");
    CHECK(lines[1] == "World");
  }

  SUBCASE("Can split a string into lines with trailing newline") {
    auto lines = SplitStringIntoLines("Yes\nNo\n");
    CHECK(lines.size() == 2);
    CHECK(lines[0] == "Yes");
    CHECK(lines[1] == "No");
  }
}

///
/// @brief Determine if a given string is all whitespace.
///
/// @param[in] line The string to check.
/// @return bool True if the string is whitespace, false otherwise.
///
static bool IsWhiteSpace(const string& line) {
  return all_of(line.begin(), line.end(), isspace);
}

///
/// @brief Convert a single line of mu text code into an Instruction.
///
/// @param[in] line The line of mu text code to parse.
/// @return Instruction The parsed instruction.
///
static Instruction ParseLine(string line) {
  if (line == "Pop")
    return Instruction{OpCode::Pop};
  else if (line.starts_with("Push"))
    return Instruction{OpCode::Push, ParseArgument(line)};

  return Instruction{GetOpCode(line)};
}

TEST_CASE("Verify ParseLine behavior") {
  SUBCASE("Can parse a line to a Pop instruction") {
    auto instruction = ParseLine("Pop");
    CHECK(instruction.opCode == OpCode::Pop);
  }

  SUBCASE("Can parse a line to a Push instruction") {
    auto instruction = ParseLine("Push i32:4");
    CHECK(instruction.opCode == OpCode::Push);
    CHECK(instruction.argument.Type() == ArgumentType::i32);
    CHECK(instruction.argument.i32() == 4);
  }

  SUBCASE("Can parse a line to an Add instruction") {
    auto instruction = ParseLine("Add");
    CHECK(instruction.opCode == OpCode::Add);
  }
}

///
/// @brief Assuming the string is a Boolean value, convert it to a bool.
///
/// @param[in] value The string to parse
/// @return bool True if the input is "true", false otherwise.
///
static bool ParseBoolFromString(string value) {
  if (value == "true")
    return true;
  if (value == "false")
    return false;
  return false;
}

///
/// @brief Parse a line of mu text code into an Argument.
///
/// @param[in] line The line of mu text code to parse.
/// @return Argument The parsed argument.
///
static Argument ParseArgument(string line) {
  auto argumentString = Trim(line.substr(line.find(" ")));

  auto colonPosition = argumentString.find(":");
  auto type = FromString(argumentString.substr(0, colonPosition));

  auto valueString = argumentString.substr(colonPosition + 1);
  int64_t value;
  if (type == ArgumentType::c) {
    value = valueString[0];
  } else if (type == ArgumentType::b) {
    value = ParseBoolFromString(valueString);
  } else {
    from_chars(valueString.data(), valueString.data() + valueString.size(),
               value);
  }

  return OfType(type, value);
}

TEST_CASE("Verify ParseArgument behavior") {
  SUBCASE("Can parse i32 argument from line") {
    auto argument = ParseArgument("unused i32:4");
    CHECK(argument.Type() == ArgumentType::i32);
    CHECK(argument.i32() == 4);
  }

  SUBCASE("Can parse i64 argument from line") {
    auto argument = ParseArgument("unused i64:4");
    CHECK(argument.Type() == ArgumentType::i64);
    CHECK(argument.i64() == 4);
  }

  SUBCASE("Can parse f32 argument from line") {
    auto argument = ParseArgument("unused f32:4");
    CHECK(argument.Type() == ArgumentType::f32);
    CHECK(argument.f32() == 4);
  }

  SUBCASE("Can parse f64 argument from line") {
    auto argument = ParseArgument("unused f64:4");
    CHECK(argument.Type() == ArgumentType::f64);
    CHECK(argument.f64() == 4);
  }

  SUBCASE("Can parse b argument from line") {
    auto argument = ParseArgument("unused b:true");
    CHECK(argument.Type() == ArgumentType::b);
    CHECK(argument.b() == true);
  }

  SUBCASE("Can parse c argument from line") {
    auto argument = ParseArgument("unused c:g");
    CHECK(argument.Type() == ArgumentType::c);
    CHECK(argument.c() == 'g');
  }
}

///
/// @brief Convert a string representing an ArgumentType to an ArgumentType.
///
/// @param[in] typeString The string to parse.
/// @return ArgumentType The parsed ArgumentType.
///
static ArgumentType FromString(string typeString) {
  if (typeString == "i32")
    return ArgumentType::i32;
  if (typeString == "i64")
    return ArgumentType::i64;
  if (typeString == "f32")
    return ArgumentType::f32;
  if (typeString == "f64")
    return ArgumentType::f64;
  if (typeString == "b")
    return ArgumentType::b;
  if (typeString == "c")
    return ArgumentType::c;
  return ArgumentType::None;
}

///
/// @brief Covert a value into an Argument of a given type.
///
/// @param[in] argumentType The type of Argument to create.
/// @param[in] value The value to convert.
/// @return Argument The converted value.
///
static Argument OfType(ArgumentType argumentType, auto value) {
  if (argumentType == ArgumentType::i32)
    return Argument((int32_t)value);
  if (argumentType == ArgumentType::i64)
    return Argument((int64_t)value);
  if (argumentType == ArgumentType::f32)
    return Argument((float)value);
  if (argumentType == ArgumentType::f64)
    return Argument((double)value);
  if (argumentType == ArgumentType::b)
    return Argument((bool)value);
  if (argumentType == ArgumentType::c)
    return Argument((char)value);
  return Argument();
}
