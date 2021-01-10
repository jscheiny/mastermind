#ifndef PARALLELIZED_GUESSER_HPP
#define PARALLELIZED_GUESSER_HPP

#include "match_table.hpp"
#include "random.hpp"
#include "utils.hpp"
#include <algorithm>

static const std::vector<int> FULL_SEARCH_SPACE = make_initial_search_space();

template<typename S>
auto make_scored_guesser(const S& score_fn, int full_space_guesses) {
    return [&score_fn, full_space_guesses](const std::vector<int>& guess_history, const std::vector<int>& search_space) -> int {
        int turn = guess_history.size();
        int should_use_full_space = turn < full_space_guesses;

        if (turn == 0) {
            return random::index(match_table::MAX_GUESS);
        }

        if (search_space.size() == 1) {
            return search_space[0];
        }

        int min_score = std::numeric_limits<int>::max();
        std::vector<int> min_score_guesses;
        const auto& guess_space = should_use_full_space ? FULL_SEARCH_SPACE : search_space;
        for (int guess : guess_space) {
            int score = score_fn(guess, search_space);
            if (score < min_score) {
                min_score = score;
                min_score_guesses.clear();
                min_score_guesses.push_back(guess);
            } else if (score == min_score) {
                min_score_guesses.push_back(guess);
            }
        }

        int random_index = random::index(min_score_guesses.size());
        return min_score_guesses[random_index];
    };
}

#endif
