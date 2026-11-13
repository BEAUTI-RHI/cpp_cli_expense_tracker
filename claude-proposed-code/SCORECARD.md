# Score Sheet: `code/main.cpp`

Scored against the project README (requirements + constraints + learning goals)
and against what a professional C++ project looks like.

**Overall: 57 / 100**
**Beginner-adjusted verdict: B-** (a real working program with the right instincts; the gaps below are normal for someone partway through a first C++ course)

| Category | Max | Score | Summary |
|---|---:|---:|---|
| Requirements (core) | 25 | 18 | Menu, add, list, total, loop all work. Totals by category only shows one chosen category, not all. |
| Correctness & robustness | 20 | 9 | Two real bugs (below) plus no validation of non-numeric input. |
| README constraints | 10 | 6 | Small functions: yes. "Use a struct/class for an expense": no, three parallel vectors instead. |
| Design / structure | 15 | 8 | Good function-per-menu-item idea; data and UI mixed together; everything in one file. |
| C++ practices | 10 | 5 | Pass-by-value copies, `using namespace std`, narrowing, `float` for money. |
| Readability & style | 10 | 6 | Clear names and helpful comments; mixed tabs/spaces, stray `;` after functions, dead code. |
| Stretch features | 5 | 0 | None attempted (filter, largest, budget). Fine, they are optional. |
| Process & tooling | 5 | 3 | Planning doc, todo and sensible commits are great. `main.exe` and `errors.txt` are committed; no build file or tests. |
| **Total** | **100** | **57** | |

## What you did well

- **You planned first** (`planning.md`) and kept a `todo.md`. Many beginners skip this.
- **Menu logic is clean**: a `bool` running flag plus a `while` loop is exactly the right pattern.
- **Functions do one job** each (`print_menu`, `show_total_by_amount`, ...), and `main()` is short.
- **You found and fixed an out-of-bounds bug** (see git log) and use `.at()` for safe indexing, which turns silent memory errors into catchable ones.
- **Reusing `record_category()`** for both adding and the by-category total shows good instinct for avoiding repeated code.
- **You saved the compiler warnings** in `errors.txt` and read them. Keep that habit.

## Bugs I reproduced by running your program

1. **Cents are thrown away.** Add `$10.75`, then "Show total": it prints `$10`.
   `size_t total_amount` (an unsigned whole number) is used to add up `float` amounts
   (`main.cpp:146`, `main.cpp:163`).
2. **Typing a letter at the menu loops forever.** `cin >> current_choice` fails on `abc`,
   the bad text is never removed from the stream, so every loop fails again instantly and
   the menu scrolls endlessly (`main.cpp:323`). The same happens at end-of-input (Ctrl+D).
3. **Same problem for the amount**: `abc` is not rejected; it silently becomes `0`
   (`main.cpp:67`). Also `0` is accepted even though an expense of nothing is meaningless.
4. **Category numbers start at `0` but the main menu starts at `1`** (`main.cpp:35`).
   Inconsistent for the user.

## What to improve (and why), in priority order

1. **Use a `struct Expense`** (README constraint). Three vectors that must stay the same
   length is fragile: one missed `push_back` and everything is misaligned. One
   `vector<Expense>` can't get out of sync. Your own `planning.md` even draws the data as a table
   of rows; a struct is that row.
2. **Read input as a whole line, then convert**, instead of `cin >> number`. This one change
   fixes bugs 2 and 3 and is the standard professional approach.
3. **Don't use `float` for money.** Store cents in an integer (`1075` = `$10.75`). `float`
   cannot store most decimals exactly, and you use `size_t` which cannot store them at all.
4. **Pass big things by `const &`**. `list_all_expenses` and `print_menu` copy whole
   vectors every call (`main.cpp:109`, `main.cpp:202`). `const vector<T>&` means "look, don't copy,
   don't change".
5. **Drop `using namespace std;`**. Fine while learning, but in larger projects it causes name
   clashes. Writing `std::` is the norm.
6. **Fix small things**: `unsigned int >= 0` is always true (`main.cpp:42`); stray `;` after
   function bodies (`main.cpp:107, 140, 156`); `endl` flushes every time, `'\n'` is faster;
   remove the unused variable and the dead `create_dummy_expense` (it would crash on an
   empty vector and its parameters are copies, so it never did anything).
7. **Replace "magic numbers"** like `chosen_option == 1/2/3/4` with an `enum class MenuOption`
   so the code reads `case MenuOption::AddExpense`.
8. **Separate "data" from "screen"**: a class that stores/calculates, and separate code that
   prints. Then you can test the calculations without typing anything.
9. **Git hygiene**: don't commit `main.exe` or `errors.txt`; add them to `.gitignore`.
10. **Add a build file (CMake) and automated tests**, so anyone can build with two commands
    and you find bugs in seconds instead of by hand.

## Learning-goal check

| Goal from README | Status |
|---|---|
| Variables, types, operators, conditionals | Yes (type choice for money needs work) |
| `if`, `switch`, loops | Yes (`switch` not used yet; `if/else if` chain is a good place for it) |
| Functions and parameters | Yes (reference vs. copy vs. `const &` is the next step) |
| `struct` and basic objects | **Not yet.** This is the main gap |
| `std::string` and `std::vector` | Yes |
| Input validation | Partial (range checks yes, bad *type* of input no) |
| Basic program decomposition | Yes, and the next step is multiple files |

See the [README](README.md) in this folder for how the proposed version addresses each point.
