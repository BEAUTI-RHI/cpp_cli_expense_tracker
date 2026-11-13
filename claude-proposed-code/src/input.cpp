#include "expense/input.hpp"

#include <charconv>
#include <istream>
#include <ostream>

#include "expense/text_utils.hpp"

namespace expense {

namespace {
constexpr std::size_t kMaxDescriptionLength = 60;
}

std::optional<std::string> prompt_line(std::istream& in, std::ostream& out,
                                       std::string_view prompt) {
    out << prompt;
    std::string line;
    if (!std::getline(in, line)) {
        return std::nullopt;  // end of input
    }
    return line;
}

std::optional<int> prompt_int_in_range(std::istream& in, std::ostream& out,
                                       std::string_view prompt, int min, int max) {
    while (true) {
        const auto line = prompt_line(in, out, prompt);
        if (!line) {
            return std::nullopt;
        }

        const std::string_view text = trim(*line);
        int value = 0;
        const auto result = std::from_chars(text.data(), text.data() + text.size(), value);
        const bool whole_text_was_a_number =
            result.ec == std::errc{} && result.ptr == text.data() + text.size();

        if (whole_text_was_a_number && value >= min && value <= max) {
            return value;
        }
        out << "Invalid choice. Please enter a number from " << min << " to " << max << ".\n";
    }
}

std::optional<Cents> prompt_amount(std::istream& in, std::ostream& out,
                                   std::string_view prompt) {
    while (true) {
        const auto line = prompt_line(in, out, prompt);
        if (!line) {
            return std::nullopt;
        }

        const auto amount = parse_money(*line);
        if (amount && *amount > 0) {
            return amount;
        }
        out << "Invalid amount. Enter a positive number with at most 2 decimals (e.g. 12.50).\n";
    }
}

std::optional<Category> prompt_category(std::istream& in, std::ostream& out) {
    int number = 1;
    for (const Category category : kAllCategories) {
        out << "  " << number << ". " << to_string(category) << '\n';
        ++number;
    }

    const int count = static_cast<int>(kAllCategories.size());
    const auto choice = prompt_int_in_range(in, out, "Select a category: ", 1, count);
    if (!choice) {
        return std::nullopt;
    }
    return kAllCategories[static_cast<std::size_t>(*choice - 1)];
}

std::optional<std::string> prompt_description(std::istream& in, std::ostream& out,
                                              std::string_view default_text) {
    while (true) {
        const auto line = prompt_line(in, out, "Short description (optional): ");
        if (!line) {
            return std::nullopt;
        }

        const std::string_view text = trim(*line);
        if (text.empty()) {
            return std::string{default_text};
        }
        if (text.size() <= kMaxDescriptionLength) {
            return std::string{text};
        }
        out << "Description is too long (max " << kMaxDescriptionLength << " characters).\n";
    }
}

}  // namespace expense
