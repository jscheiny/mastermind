#include "match_table.hpp"
#include "smart_evaluator.hpp"

auto smart_evaluator::operator()(int guess, const secret_space& possible_secrets) const -> int {
    const auto& table = match_table::instance();
    int metric = 0;
    for (int secret : possible_secrets) {
        match_value match = table.get_match(guess, secret);
        metric += possible_secrets.get_narrowed_size(guess, match);
    }
    return metric;
}
