#ifndef PARALLELIZED_GUESSER_HPP
#define PARALLELIZED_GUESSER_HPP

#include "console.hpp"
#include "match_table.hpp"
#include "random.hpp"
#include <algorithm>
#include <functional>
#include <future>

template<typename S>
auto make_scored_guesser(
    const S& score_fn,
    int threads = std::thread::hardware_concurrency()
) {
    return [&score_fn, threads](const std::vector<int>& guess_history, const std::vector<int>& search_space) -> int {
        if (guess_history.empty()) {
            return random::index(match_table::MAX_GUESS);
        }

        if (search_space.size() == 1) {
            return search_space[0];
        }

        int min_score = std::numeric_limits<int>::max();
        std::vector<int> min_score_guesses;
        for (int guess : search_space) {
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
