#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace expense {

// Money is stored as a whole number of cents (1250 == $12.50).
// float/double cannot represent most decimal values exactly (0.1 + 0.2 != 0.3),
// so adding many of them slowly drifts. Integers never drift.
using Cents = std::int64_t;

// Turns text such as "12", "12.5" or "12.50" into cents.
// Returns std::nullopt if the text is not a valid non-negative amount
// (letters, a minus sign, more than 2 decimals, absurdly large numbers...).
std::optional<Cents> parse_money(std::string_view text);

// Turns cents back into text: 1250 -> "$12.50".
std::string format_money(Cents cents);

}  // namespace expense
