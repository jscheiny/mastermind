#include "match_table.hpp"
#include "smart_guesser.hpp"

auto smart_guesser::evaluate_guess(int guess) const -> int {
    const auto& table = match_table::instance();
    int metric = 0;
    for (int secret : possible_secrets_) {
        match_value match = table.get_match(guess, secret);
        metric += possible_secrets_.get_narrowed_size(guess, match);
    }
    return metric;
}
