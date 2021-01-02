#include "abstract_guesser.hpp"
#include "match_table.hpp"
#include <numeric>

auto abstract_guesser::reset() -> void {
    guess_history_.clear();

    possible_secrets_ = std::vector<int>(match_table::MAX_GUESS, 0);
    std::iota(possible_secrets_.begin(), possible_secrets_.end(), 0);
}

auto abstract_guesser::update(int guess, match_value match) -> void {
    guess_history_.push_back(guess);

    const auto& table = match_table::instance();
    std::vector<int> new_possible_secrets;
    for (int secret : possible_secrets_) {
        if (table.get_match(guess, secret) == match && secret != guess) {
            new_possible_secrets.push_back(secret);
        }
    }
    possible_secrets_ = std::move(new_possible_secrets);
}
