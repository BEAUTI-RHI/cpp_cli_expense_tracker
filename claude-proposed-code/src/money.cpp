#include "expense/money.hpp"

#include <cstddef>
#include <iomanip>
#include <sstream>

#include "expense/text_utils.hpp"

namespace expense {

namespace {

bool is_digit(char c) { return c >= '0' && c <= '9'; }

// 12 digits before the decimal point keeps every possible total far below
// the limit of a 64-bit integer.
constexpr std::size_t kMaxWholeDigits = 12;
constexpr int kCentsPerUnit = 100;

}  // namespace

std::optional<Cents> parse_money(std::string_view text) {
    text = trim(text);
    if (text.empty()) {
        return std::nullopt;
    }

    std::size_t pos = 0;

    // Part before the decimal point.
    Cents whole = 0;
    std::size_t whole_digits = 0;
    while (pos < text.size() && is_digit(text[pos])) {
        whole = whole * 10 + (text[pos] - '0');
        ++whole_digits;
        ++pos;
        if (whole_digits > kMaxWholeDigits) {
            return std::nullopt;
        }
    }

    // Optional part after the decimal point (at most 2 digits).
    Cents fraction = 0;
    std::size_t fraction_digits = 0;
    if (pos < text.size() && text[pos] == '.') {
        ++pos;
        while (pos < text.size() && is_digit(text[pos])) {
            if (fraction_digits == 2) {
                return std::nullopt;  // "1.234" has too many decimals
            }
            fraction = fraction * 10 + (text[pos] - '0');
            ++fraction_digits;
            ++pos;
        }
    }

    // Anything left over (letters, '-', a second '.') makes it invalid.
    if (pos != text.size()) {
        return std::nullopt;
    }
    if (whole_digits == 0 && fraction_digits == 0) {
        return std::nullopt;  // just "." or similar
    }
    if (fraction_digits == 1) {
        fraction *= 10;  // "12.5" means 50 cents, not 5
    }

    return whole * kCentsPerUnit + fraction;
}

std::string format_money(Cents cents) {
    const bool negative = cents < 0;
    const Cents absolute = negative ? -cents : cents;

    std::ostringstream out;
    if (negative) {
        out << '-';
    }
    out << '$' << absolute / kCentsPerUnit << '.' << std::setw(2) << std::setfill('0')
        << absolute % kCentsPerUnit;
    return out.str();
}

}  // namespace expense
