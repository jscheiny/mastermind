#include "match_table.hpp"
#include "smart_evaluator.hpp"

auto get_narrowed_size(const std::vector<int>& search_space, int guess, const match_value& match) -> int;

auto smart_evaluator::operator()(int guess, const std::vector<int>& search_space) const -> int {
    const auto& table = match_table::instance();
    int metric = 0;
    for (int secret : search_space) {
        match_value match = table.get_match(guess, secret);
        metric += get_narrowed_size(search_space, guess, match);
    }
    return metric;
}

auto get_narrowed_size(const std::vector<int>& search_space, int guess, const match_value& match) -> int {
    const auto& table = match_table::instance();
    int count = 0;
    for (int secret : search_space) {
        if (table.get_match(guess, secret) == match) {
            count++;
        }
    }
    return count;
}
