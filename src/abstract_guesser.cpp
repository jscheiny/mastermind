#include "abstract_guesser.hpp"
#include "match_table.hpp"
#include <numeric>

auto abstract_guesser::reset() -> void {
    guess_history_.clear();

    search_space_ = std::vector<int>(match_table::MAX_GUESS, 0);
    std::iota(search_space_.begin(), search_space_.end(), 0);
}

auto abstract_guesser::update(int guess, match_value match) -> void {
    guess_history_.push_back(guess);

    const auto& table = match_table::instance();
    std::vector<int> new_search_space;
    for (int secret : search_space_) {
        if (table.get_match(guess, secret) == match && secret != guess) {
            new_search_space.push_back(secret);
        }
    }
    search_space_ = std::move(new_search_space);
}
