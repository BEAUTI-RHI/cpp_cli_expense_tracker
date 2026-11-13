#include "expense/tracker.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>
#include <utility>

namespace expense {

void ExpenseTracker::add(Expense expense) {
    expenses_.push_back(std::move(expense));
}

Cents ExpenseTracker::total() const {
    return std::accumulate(expenses_.begin(), expenses_.end(), Cents{0},
                           [](Cents sum, const Expense& e) { return sum + e.amount; });
}

Cents ExpenseTracker::total_for(Category category) const {
    Cents sum = 0;
    for (const Expense& e : expenses_) {
        if (e.category == category) {
            sum += e.amount;
        }
    }
    return sum;
}

std::map<Category, Cents> ExpenseTracker::totals_by_category() const {
    std::map<Category, Cents> totals;
    for (const Expense& e : expenses_) {
        totals[e.category] += e.amount;  // a missing key starts at 0
    }
    return totals;
}

std::vector<Expense> ExpenseTracker::filter_by_category(Category category) const {
    std::vector<Expense> matches;
    std::copy_if(expenses_.begin(), expenses_.end(), std::back_inserter(matches),
                 [category](const Expense& e) { return e.category == category; });
    return matches;
}

std::optional<Expense> ExpenseTracker::largest() const {
    if (expenses_.empty()) {
        return std::nullopt;
    }
    return *std::max_element(
        expenses_.begin(), expenses_.end(),
        [](const Expense& a, const Expense& b) { return a.amount < b.amount; });
}

bool ExpenseTracker::is_over_budget() const {
    return budget_.has_value() && total() > *budget_;
}

}  // namespace expense
