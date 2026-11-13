#pragma once

#include <map>
#include <optional>
#include <vector>

#include "expense/expense.hpp"
#include "expense/money.hpp"

namespace expense {

// Holds all expenses in memory and answers questions about them.
// It knows nothing about the keyboard or the screen - that is the job of the
// App class. Keeping "what the data is" apart from "how we show it" means this
// class can be tested without typing anything.
class ExpenseTracker {
public:
    void add(Expense expense);

    const std::vector<Expense>& expenses() const { return expenses_; }
    bool empty() const { return expenses_.empty(); }

    Cents total() const;
    Cents total_for(Category category) const;

    // Only categories that actually have spending are included.
    std::map<Category, Cents> totals_by_category() const;

    std::vector<Expense> filter_by_category(Category category) const;

    // std::nullopt when there are no expenses yet.
    std::optional<Expense> largest() const;

    // Budget (stretch feature). The program is in-memory only, so "monthly"
    // means "for this session".
    void set_budget(Cents budget) { budget_ = budget; }
    std::optional<Cents> budget() const { return budget_; }
    bool is_over_budget() const;

private:
    std::vector<Expense> expenses_;
    std::optional<Cents> budget_;
};

}  // namespace expense
