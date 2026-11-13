#include "expense/expense.hpp"

namespace expense {

std::string_view to_string(Category category) {
    // No `default:` on purpose: if you add a new Category and forget it here,
    // the compiler warns you.
    switch (category) {
        case Category::Housing:    return "Housing";
        case Category::Utilities:  return "Utilities";
        case Category::Food:       return "Food";
        case Category::Transport:  return "Transport";
        case Category::Insurance:  return "Insurance";
        case Category::Healthcare: return "Healthcare";
        case Category::Leisure:    return "Leisure";
        case Category::Shopping:   return "Shopping";
        case Category::Savings:    return "Savings";
        case Category::Debt:       return "Debt";
        case Category::Travel:     return "Travel";
        case Category::Other:      return "Other";
    }
    return "Unknown";  // only reached if someone passes an invalid value
}

}  // namespace expense
