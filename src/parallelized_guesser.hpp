#ifndef PARALLELIZED_GUESSER_HPP
#define PARALLELIZED_GUESSER_HPP

#include "console.hpp"
#include "match_table.hpp"
#include "parallelized_guesser.hpp"
#include "random.hpp"
#include <algorithm>
#include <functional>
#include <future>

namespace impl {
    struct best_guess {
        int guess;
        int score;
    };

    template<typename S>
    auto find_best_guess(const std::vector<int>& search_space, const S& score_fn, int threads, int offset) -> best_guess;
}

template<typename S>
auto make_parallelized_guesser(
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

        if (search_space.size() < threads || threads == 1) {
            return impl::find_best_guess(search_space, score_fn, 1, 0).guess;
        }

        std::vector<std::future<impl::best_guess>> futures;
        for (int offset = 0; offset < threads; offset++) {
            futures.push_back(
                std::async(std::launch::async, [&search_space, &score_fn, threads, offset]() {
                    return impl::find_best_guess(search_space, score_fn, threads, offset);
                })
            );
        }

        std::vector<impl::best_guess> results;
        for (auto& future : futures) {
            results.push_back(future.get());
        }

        random::shuffle(results.begin(), results.end());
        auto min = std::min_element(results.begin(), results.end(), [](impl::best_guess a, impl::best_guess b) {
            return a.score < b.score;
        });
        return min->guess;
    };
}

template<typename S>
auto make_simple_guesser(const S& score_fn) {
    return make_parallelized_guesser(score_fn, 1);
}

template<typename S>
auto impl::find_best_guess(const std::vector<int>& search_space, const S& score_fn, int threads, int offset) -> best_guess {
    int min_score = std::numeric_limits<int>::max();
    std::vector<int> min_guesses;
    for (int index = offset; index < search_space.size(); index += threads) {
        int guess = search_space[index];
        int score = score_fn(guess, search_space);
        if (score < min_score) {
            min_score = score;
            min_guesses.clear();
            min_guesses.push_back(guess);
        } else if (score == min_score) {
            min_guesses.push_back(guess);
        }
    }

    int random_index = random::index(min_guesses.size());
    return { .guess = min_guesses[random_index], .score = min_score };
}

#endif
