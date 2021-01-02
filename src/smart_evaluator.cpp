#include "match_table.hpp"
#include "smart_evaluator.hpp"

auto get_narrowed_size(const std::vector<int>& possible_secrets, int guess, const match_value& match) -> int;

auto smart_evaluator::operator()(int guess, const std::vector<int>& possible_secrets) const -> int {
    const auto& table = match_table::instance();
    int metric = 0;
    for (int secret : possible_secrets) {
        match_value match = table.get_match(guess, secret);
        metric += get_narrowed_size(possible_secrets, guess, match);
    }
    return metric;
}

auto get_narrowed_size(const std::vector<int>& possible_secrets, int guess, const match_value& match) -> int {
    const auto& table = match_table::instance();
    int count = 0;
    for (int secret : possible_secrets) {
        if (table.get_match(guess, secret) == match) {
            count++;
        }
    }
    return count;
}
