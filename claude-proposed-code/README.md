# CLI Expense Tracker: proposed version

A terminal app to record small daily expenses and review them. Data lives in
memory only (no database), as required by the project PRD.

## Build and run

```sh
cmake -S . -B build
cmake --build build
./build/expense_tracker      # run the program
./build/run_tests            # run the tests (or: cd build && ctest)
```

Needs a C++17 compiler (g++ / clang++) and CMake 3.16+.

## Features

Required: text menu, add an expense (amount, category, description), list all,
total spent, totals by category, input validation, runs until Exit.

Stretch (all done): filter by category, largest expense, budget with a warning
when exceeded ("monthly" means "for this session", since nothing is saved).

## How the code is organised

```
include/expense/   headers (what each piece offers)
src/               implementations (how it does it)
tests/             automated tests
```

| File | Responsibility | Learning-goal it demonstrates |
|---|---|---|
| `money.*` | Parse `"12.50"` to cents, format cents back to `"$12.50"` | Types, validation |
| `expense.*` | `struct Expense` and `enum class Category` | struct, enum, switch |
| `tracker.*` | `ExpenseTracker`: stores expenses, computes totals/filter/largest | vector, classes, algorithms |
| `input.*` | Safe prompts that re-ask until valid | loops, validation |
| `app.*` | The menu and one function per menu item | decomposition |
| `main.cpp` | Starts the app (5 lines) | |

The key idea: **each file has one job.** `tracker` never prints and never reads the
keyboard; `input` never does maths; `app` glues them together. That is why the
calculations can be tested without typing anything.

## Design decisions (and why)

- **Money is stored as integer cents**, not `float`. `0.1f + 0.2f != 0.3f`; integers are exact.
- **Input is read as a whole line**, then converted. Typing `abc` where a number is expected can
  never jam the input stream (the infinite-loop bug in the original).
- **End-of-input is handled.** Ctrl+D exits cleanly rather than looping forever.
- **`enum class Category`** instead of strings: a typo is a compile error, not a silent new category.
- **`const &` parameters** where data is only read, so nothing is copied or accidentally changed.
- **Streams are passed into `App`** (`std::istream&`, `std::ostream&`), so tests can feed fake
  keyboard input and read the output.
- **Strict compiler warnings** are on (`-Wall -Wextra -Wpedantic -Wconversion -Wshadow`) and the code compiles with none.

## Where to read first

Suggested order: `expense.hpp` (the data), `tracker.cpp` (the logic), `input.cpp`
(validation), `app.cpp` (the menu), then `tests/tests.cpp`.
