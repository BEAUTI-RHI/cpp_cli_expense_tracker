#pragma once

#include <string_view>

namespace expense {

// Returns the text without leading/trailing spaces, tabs and line endings.
inline std::string_view trim(std::string_view text) {
    constexpr std::string_view whitespace = " \t\r\n";
    const auto first = text.find_first_not_of(whitespace);
    if (first == std::string_view::npos) {
        return {};  // the text was empty or only whitespace
    }
    const auto last = text.find_last_not_of(whitespace);
    return text.substr(first, last - first + 1);
}

}  // namespace expense
