#include "expense/app.hpp"

#include <iomanip>
#include <istream>
#include <ostream>

#include "expense/input.hpp"

namespace expense {

namespace {
constexpr int kMenuSize = 8;  // keep in sync with App::MenuOption
}

void App::run() {
    out_ << "Welcome to CLI Expense Tracker!\n";

    bool running = true;
    while (running) {
        print_menu();
        const auto choice = prompt_int_in_range(in_, out_, "Pick an option: ", 1, kMenuSize);
        if (!choice) {
            break;  // input ended (Ctrl+D) - leave cleanly instead of looping forever
        }
        running = handle(static_cast<MenuOption>(*choice));
    }

    out_ << "Goodbye!\n";
}

void App::print_menu() {
    out_ << "\n=== Menu ===\n"
         << "1. Add an expense\n"
         << "2. List all expenses\n"
         << "3. Show total spent\n"
         << "4. Show totals by category\n"
         << "5. Filter expenses by category\n"
         << "6. Show largest expense\n"
         << "7. Set monthly budget\n"
         << "8. Exit\n";
}

bool App::handle(MenuOption option) {
    out_ << '\n';
    switch (option) {
        case MenuOption::AddExpense:           add_expense();             break;
        case MenuOption::ListExpenses:         list_expenses();           break;
        case MenuOption::ShowTotal:            show_total();              break;
        case MenuOption::ShowTotalsByCategory: show_totals_by_category(); break;
        case MenuOption::FilterByCategory:     filter_by_category();      break;
        case MenuOption::ShowLargest:          show_largest();            break;
        case MenuOption::SetBudget:            set_budget();              break;
        case MenuOption::Exit:                 return false;
    }
    return true;
}

void App::add_expense() {
    const auto amount = prompt_amount(in_, out_, "Amount: ");
    if (!amount) return;

    out_ << "Categories:\n";
    const auto category = prompt_category(in_, out_);
    if (!category) return;

    const auto description = prompt_description(in_, out_, "(no description)");
    if (!description) return;

    tracker_.add(Expense{*amount, *category, *description});
    out_ << "\nRecorded: " << format_money(*amount) << " | " << to_string(*category) << " | "
         << *description << '\n';
    print_budget_warning_if_needed();
}

void App::print_table(const std::vector<Expense>& expenses) {
    out_ << std::left << std::setw(4) << "ID" << std::right << std::setw(12) << "Amount"
         << "  " << std::left << std::setw(12) << "Category" << "Description\n";

    int id = 1;
    for (const Expense& e : expenses) {
        out_ << std::left << std::setw(4) << id << std::right << std::setw(12)
             << format_money(e.amount) << "  " << std::left << std::setw(12)
             << to_string(e.category) << e.description << '\n';
        ++id;
    }
}

void App::list_expenses() {
    if (tracker_.empty()) {
        out_ << "No expenses recorded yet.\n";
        return;
    }
    print_table(tracker_.expenses());
}

void App::show_total() {
    if (tracker_.empty()) {
        out_ << "No expenses recorded yet.\n";
        return;
    }
    out_ << "Total spent: " << format_money(tracker_.total()) << '\n';
    print_budget_warning_if_needed();
}

void App::show_totals_by_category() {
    const auto totals = tracker_.totals_by_category();
    if (totals.empty()) {
        out_ << "No expenses recorded yet.\n";
        return;
    }
    for (const auto& [category, amount] : totals) {
        out_ << std::left << std::setw(12) << to_string(category) << std::right << std::setw(12)
             << format_money(amount) << '\n';
    }
    out_ << std::left << std::setw(12) << "TOTAL" << std::right << std::setw(12)
         << format_money(tracker_.total()) << '\n';
}

void App::filter_by_category() {
    if (tracker_.empty()) {
        out_ << "No expenses recorded yet.\n";
        return;
    }
    out_ << "Categories:\n";
    const auto category = prompt_category(in_, out_);
    if (!category) return;

    const auto matches = tracker_.filter_by_category(*category);
    out_ << '\n';
    if (matches.empty()) {
        out_ << "No expenses in " << to_string(*category) << ".\n";
        return;
    }
    print_table(matches);
    out_ << "Total for " << to_string(*category) << ": "
         << format_money(tracker_.total_for(*category)) << '\n';
}

void App::show_largest() {
    const auto largest = tracker_.largest();
    if (!largest) {
        out_ << "No expenses recorded yet.\n";
        return;
    }
    out_ << "Largest expense: " << format_money(largest->amount) << " | "
         << to_string(largest->category) << " | " << largest->description << '\n';
}

void App::set_budget() {
    const auto budget = prompt_amount(in_, out_, "Monthly budget: ");
    if (!budget) return;

    tracker_.set_budget(*budget);
    out_ << "Budget set to " << format_money(*budget) << ".\n";
    print_budget_warning_if_needed();
}

void App::print_budget_warning_if_needed() {
    if (tracker_.is_over_budget()) {
        out_ << "WARNING: you are over your budget! Spent " << format_money(tracker_.total())
             << " of " << format_money(*tracker_.budget()) << ".\n";
    }
}

}  // namespace expense
