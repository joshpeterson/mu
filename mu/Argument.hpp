#pragma once

#include <cassert>
#include <cstdint>

#include <fmt/core.h>
#include <fmt/format.h>

///
/// @brief All of the possible argument types
///
enum class ArgumentType { None, i64, i32, f32, f64, b, c };

///
/// @brief A union representing all of the possible Argument types.
///
union ArgumentData {
  int64_t i64;
  int32_t i32;
  float f32;
  double f64;
  bool b;
  char c;
};

///
/// @brief A value of a given size and an associated type.
/// Each opcode can have one or more arguments associated with it.
///
struct Argument {
  ///
  /// @brief The default constructor. ArgumentType here is None.
  ///
  constexpr Argument() : m_Type(ArgumentType::None) {}

  ///
  /// @brief Create an Argument from a 32-bit integer.
  ///
  /// @param[in] value A 32-bit integer to store in the Argument.
  ///
  constexpr Argument(int32_t value) : m_Type(ArgumentType::i32) {
    m_Data.i32 = value;
  }

  ///
  /// @brief Create an Argument from a 64-bit integer.
  ///
  /// @param[in] value A 64-bit integer to store in the Argument.
  ///
  constexpr Argument(int64_t value) : m_Type(ArgumentType::i64) {
    m_Data.i64 = value;
  }

  ///
  /// @brief Create an Argument from a 64-bit float.
  ///
  /// @param[in] value A 64-bit float to store in the Argument.
  ///
  constexpr Argument(float value) : m_Type(ArgumentType::f32) {
    m_Data.f32 = value;
  }

  ///
  /// @brief Create an Argument from a 64-bit float.
  ///
  /// @param[in] value A 64-bit float to store in the Argument.
  ///
  constexpr Argument(double value) : m_Type(ArgumentType::f64) {
    m_Data.f64 = value;
  }

  ///
  /// @brief Create an Argument from a Boolean value.
  ///
  /// @param[in] value A Boolean to store in the Argument.
  ///
  constexpr Argument(bool value) : m_Type(ArgumentType::b) { m_Data.b = value; }

  ///
  /// @brief Create an Argument from a character value.
  ///
  /// @param[in] value A character to store in the Argument.
  ///
  constexpr Argument(char value) : m_Type(ArgumentType::c) { m_Data.c = value; }

  ArgumentType Type() const;

  int64_t i64() const;
  int32_t i32() const;
  float f32() const;
  double f64() const;
  bool b() const;
  char c() const;

private:
  ArgumentType m_Type;
  ArgumentData m_Data;
};

bool operator==(const Argument& left, const Argument& right);

///
/// @brief Allow the fmt library to format an Argument.
///
template <> struct fmt::formatter<Argument> {
  constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
    auto it = ctx.begin(), end = ctx.end();

    // Check if reached the end of the range:
    if (it != end && *it != '}')
      throw format_error("invalid format");

    // Return an iterator past the end of the parsed range:
    return it;
  }

  template <typename FormatContext>
  auto format(const Argument& argument, FormatContext& ctx) const
      -> decltype(ctx.out()) {
    switch (argument.Type()) {
    case ArgumentType::None:
      return fmt::format_to(ctx.out(), "No argument");
    case ArgumentType::i32:
      return fmt::format_to(ctx.out(), "{} (i32)", argument.i32());
    case ArgumentType::i64:
      return fmt::format_to(ctx.out(), "{} (i64)", argument.i64());
    case ArgumentType::f32:
      return fmt::format_to(ctx.out(), "{} (f32)", argument.f32());
    case ArgumentType::f64:
      return fmt::format_to(ctx.out(), "{} (f64)", argument.f64());
    case ArgumentType::b:
      return fmt::format_to(ctx.out(), "{} (bool)", argument.b());
    case ArgumentType::c:
      return fmt::format_to(ctx.out(), "{} (char)", argument.c());
    default:
      assert(0 && "Missing Argument formatting case");
    }
    return ctx.out();
  }
};
