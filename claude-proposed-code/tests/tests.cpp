// A tiny test runner with no external libraries.
// Professional projects usually use a framework (Catch2, GoogleTest), but the
// idea is the same: run the code, compare with what you expect, report failures.

#include <iostream>
#include <sstream>
#include <string>

#include "expense/app.hpp"
#include "expense/money.hpp"
#include "expense/tracker.hpp"

namespace {

int failures = 0;

#define CHECK(condition)                                                              \
    do {                                                                              \
        if (!(condition)) {                                                           \
            ++failures;                                                               \
            std::cerr << "FAILED " << __FILE__ << ":" << __LINE__ << "  " #condition  \
                      << '\n';                                                        \
        }                                                                             \
    } while (false)

using namespace expense;

void test_parse_money() {
    CHECK(parse_money("12") == 1200);
    CHECK(parse_money("12.5") == 1250);
    CHECK(parse_money("12.50") == 1250);
    CHECK(parse_money("0.05") == 5);
    CHECK(parse_money(".99") == 99);
    CHECK(parse_money("  7.25  ") == 725);

    CHECK(!parse_money(""));
    CHECK(!parse_money("abc"));
    CHECK(!parse_money("-5"));
    CHECK(!parse_money("1.234"));
    CHECK(!parse_money("1.2.3"));
    CHECK(!parse_money("12abc"));
    CHECK(!parse_money("."));
    CHECK(!parse_money("99999999999999999999"));
}

void test_format_money() {
    CHECK(format_money(1250) == "$12.50");
    CHECK(format_money(5) == "$0.05");
    CHECK(format_money(0) == "$0.00");
    CHECK(format_money(-250) == "-$2.50");
}

void test_tracker() {
    ExpenseTracker tracker;
    CHECK(tracker.empty());
    CHECK(tracker.total() == 0);
    CHECK(!tracker.largest());

    tracker.add({1075, Category::Food, "lunch"});
    tracker.add({2500, Category::Transport, "bus pass"});
    tracker.add({425, Category::Food, "coffee"});

    CHECK(tracker.total() == 4000);  // cents are NOT lost
    CHECK(tracker.total_for(Category::Food) == 1500);
    CHECK(tracker.total_for(Category::Debt) == 0);
    CHECK(tracker.totals_by_category().size() == 2);
    CHECK(tracker.filter_by_category(Category::Food).size() == 2);
    CHECK(tracker.largest()->description == "bus pass");

    CHECK(!tracker.is_over_budget());  // no budget set yet
    tracker.set_budget(4000);
    CHECK(!tracker.is_over_budget());  // exactly on budget is fine
    tracker.set_budget(3999);
    CHECK(tracker.is_over_budget());
}

// Runs the whole program with fake keyboard input and returns what it printed.
std::string run_app(const std::string& typed) {
    std::istringstream in(typed);
    std::ostringstream out;
    App(in, out).run();
    return out.str();
}

bool contains(const std::string& text, const std::string& part) {
    return text.find(part) != std::string::npos;
}

void test_app_happy_path() {
    // add $10.75 Food "lunch", then list, then total, then exit
    const std::string out = run_app("1\n10.75\n3\nlunch\n2\n3\n8\n");
    CHECK(contains(out, "Recorded: $10.75 | Food | lunch"));
    CHECK(contains(out, "Total spent: $10.75"));
    CHECK(contains(out, "Goodbye!"));
}

void test_app_rejects_bad_input() {
    // Garbage at the menu, then a negative amount, then letters as an amount,
    // then a valid amount; a bad category number; then exit.
    const std::string out = run_app("abc\n99\n1\n-5\nxyz\n5\n0\n4\n\n8\n");
    CHECK(contains(out, "Invalid choice"));
    CHECK(contains(out, "Invalid amount"));
    CHECK(contains(out, "Recorded: $5.00 | Transport | (no description)"));
}

void test_app_survives_end_of_input() {
    // No "Exit" typed: input just ends. Must stop, not loop forever.
    const std::string out = run_app("abc\n");
    CHECK(contains(out, "Goodbye!"));
}

void test_app_budget_warning() {
    const std::string out = run_app("7\n10\n1\n20\n3\n\n8\n");
    CHECK(contains(out, "WARNING"));
}

void test_app_empty_states() {
    const std::string out = run_app("2\n3\n4\n6\n8\n");
    CHECK(contains(out, "No expenses recorded yet."));
}

}  // namespace

int main() {
    test_parse_money();
    test_format_money();
    test_tracker();
    test_app_happy_path();
    test_app_rejects_bad_input();
    test_app_survives_end_of_input();
    test_app_budget_warning();
    test_app_empty_states();

    if (failures == 0) {
        std::cout << "All tests passed.\n";
        return 0;
    }
    std::cerr << failures << " check(s) failed.\n";
    return 1;
}
