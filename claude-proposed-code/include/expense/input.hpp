#pragma once

#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>

#include "expense/expense.hpp"
#include "expense/money.hpp"

// Safe ways to ask the user for things.
//
// Every function:
//   * keeps asking until the answer is valid, printing a helpful message
//   * reads a whole line, so a bad entry like "abc" can never get stuck in
//     the input stream and cause an endless loop
//   * returns std::nullopt only when the input ended (Ctrl+D / end of file)
//
// The streams are passed in (instead of using std::cin/std::cout directly)
// so the tests can feed in fake input.

namespace expense {

std::optional<std::string> prompt_line(std::istream& in, std::ostream& out,
                                       std::string_view prompt);

std::optional<int> prompt_int_in_range(std::istream& in, std::ostream& out,
                                       std::string_view prompt, int min, int max);

// Asks for a positive amount such as 12.50.
std::optional<Cents> prompt_amount(std::istream& in, std::ostream& out,
                                   std::string_view prompt);

// Shows the numbered category list and asks the user to pick one.
std::optional<Category> prompt_category(std::istream& in, std::ostream& out);

// Optional text: an empty answer becomes `default_text`.
std::optional<std::string> prompt_description(std::istream& in, std::ostream& out,
                                              std::string_view default_text);

}  // namespace expense
