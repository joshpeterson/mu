#pragma once

#include <cassert>
#include <cstdint>

#include <fmt/core.h>
#include <fmt/format.h>

enum class ArgumentType { None, i64, i32, f32, f64, b, c };

union ArgumentData {
  int64_t i64;
  int32_t i32;
  float f32;
  double f64;
  bool b;
  char c;
};

struct Argument {
  Argument();
  Argument(int32_t value);
  Argument(int64_t value);
  Argument(float value);
  Argument(double value);
  Argument(bool value);
  Argument(char value);

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