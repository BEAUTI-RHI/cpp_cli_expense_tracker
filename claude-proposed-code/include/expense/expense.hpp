#pragma once

#include <array>
#include <string>
#include <string_view>

#include "expense/money.hpp"

namespace expense {

// An enum class gives each category a name the compiler can check.
// With plain strings, a typo like "Fod" compiles fine and silently creates a
// brand-new category. With an enum, a typo is a compile error.
enum class Category {
    Housing,
    Utilities,
    Food,
    Transport,
    Insurance,
    Healthcare,
    Leisure,
    Shopping,
    Savings,
    Debt,
    Travel,
    Other,
};

// Every category in menu order, so the program can loop over them.
inline constexpr std::array<Category, 12> kAllCategories = {
    Category::Housing,   Category::Utilities, Category::Food,     Category::Transport,
    Category::Insurance, Category::Healthcare, Category::Leisure, Category::Shopping,
    Category::Savings,   Category::Debt,      Category::Travel,   Category::Other,
};

std::string_view to_string(Category category);

// One recorded expense. A struct keeps the three related values together,
// instead of three separate vectors that must always stay in sync.
struct Expense {
    Cents amount{0};
    Category category{Category::Other};
    std::string description;
};

}  // namespace expense
