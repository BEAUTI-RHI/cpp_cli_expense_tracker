#pragma once

#include <iosfwd>

#include "expense/tracker.hpp"

namespace expense {

// The text menu and the code behind each menu item.
class App {
public:
    App(std::istream& in, std::ostream& out) : in_(in), out_(out) {}

    // Runs until the user picks Exit (or the input ends).
    void run();

private:
    // Numbers match what the user sees in the menu.
    enum class MenuOption {
        AddExpense = 1,
        ListExpenses,
        ShowTotal,
        ShowTotalsByCategory,
        FilterByCategory,
        ShowLargest,
        SetBudget,
        Exit,
    };

    void print_menu();
    // Returns false when the program should stop.
    bool handle(MenuOption option);

    void add_expense();
    void list_expenses();
    void show_total();
    void show_totals_by_category();
    void filter_by_category();
    void show_largest();
    void set_budget();

    void print_table(const std::vector<Expense>& expenses);
    void print_budget_warning_if_needed();

    std::istream& in_;
    std::ostream& out_;
    ExpenseTracker tracker_;
};

}  // namespace expense
