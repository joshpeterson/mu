#pragma once

#include <cassert>
#include <cstdint>

#include <fmt/core.h>
#include <fmt/format.h>

enum class ArgumentType { None, i64, i32, f32 };

union ArgumentData {
  int64_t i64;
  int32_t i32;
  float f32;
};

struct Argument {
  Argument();
  Argument(int32_t value);
  Argument(int64_t value);
  Argument(float value);

  ArgumentType Type() const;

  int64_t i64() const;
  int32_t i32() const;
  float f32() const;

private:
  ArgumentType m_Type;
  ArgumentData m_Data;
};

bool operator==(const Argument& left, const Argument& right);

template <> struct fmt::formatter<Argument> : formatter<string_view> {
  // parse is inherited from formatter<string_view>.
  template <typename FormatContext>
  auto format(Argument c, FormatContext& ctx) {
    string_view name = "unknown";
    switch (c.Type()) {
    case ArgumentType::None:
      name = "No argument";
      break;
    case ArgumentType::i32:
      name = fmt::format("{} (i32)", c.i32());
      break;
    case ArgumentType::i64:
      name = fmt::format("{} (i64)", c.i64());
      break;
    }
    return formatter<string_view>::format(name, ctx);
  }
};