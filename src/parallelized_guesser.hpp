#ifndef PARALLELIZED_GUESSER_HPP
#define PARALLELIZED_GUESSER_HPP

#include "console.hpp"
#include "match_table.hpp"
#include "parallelized_guesser.hpp"
#include "random.hpp"
#include "scoped_timer.hpp"
#include <algorithm>
#include <functional>
#include <future>

template <typename E>
class parallelized_guesser{
public:
    parallelized_guesser(
        E evaluate_guess,
        int threads = std::thread::hardware_concurrency()
    ): evaluate_guess_{evaluate_guess}, threads_{threads} {}

    auto operator()(const std::vector<int>& guess_history, const std::vector<int>& search_space) const -> int;

private:
    E evaluate_guess_;
    const int threads_;

    struct best_guess {
        int guess;
        int metric;
    };

    auto find_best_guess(const std::vector<int>& search_space, int offset) const -> best_guess;
};

template <typename E>
auto parallelized_guesser<E>::operator()(
    const std::vector<int>& guess_history,
    const std::vector<int>& search_space
) const -> int {
    scoped_timer move_timer{"Make guess"};
    std::cout 
        << "Choosing among " 
        << console::green_fg 
        << search_space.size() 
        << console::reset 
        << " possible guesses" 
        << std::endl;

    if (guess_history.empty()) {
        return random::range(0, match_table::MAX_GUESS - 1);
    }

    if (search_space.size() == 1) {
        return search_space[0];
    }

    if (search_space.size() < threads_ || threads_ == 1) {
        return find_best_guess(search_space, 0).guess;
    }

    std::vector<std::future<best_guess>> futures;

    for (int offset = 0; offset < threads_; offset++) {
        futures.push_back(
            std::async(
                std::launch::async, 
                [this, offset, &search_space]() { return find_best_guess(search_space, offset); }
            )
        );
    }

    std::vector<best_guess> results;
    for (auto& future : futures) {
        results.push_back(future.get());
    }

    random::shuffle(results.begin(), results.end());
    auto min = std::min_element(results.begin(), results.end(), [](best_guess a, best_guess b) { return a.metric < b.metric; });
    return min->guess;
}

template<typename E>
auto parallelized_guesser<E>::find_best_guess(const std::vector<int>& search_space, int offset) const -> best_guess {
    int min_metric = std::numeric_limits<int>::max();
    std::vector<int> min_guesses;
    for (int index = offset; index < search_space.size(); index += threads_) {
        int guess = search_space[index];
        int metric = evaluate_guess_(guess, search_space);
        if (metric < min_metric) {
            min_metric = metric;
            min_guesses.clear();
            min_guesses.push_back(guess);
        } else if (metric == min_metric) {
            min_guesses.push_back(guess);
        }
    }

    int random_index = random::range(0, min_guesses.size() - 1);
    return {.guess = min_guesses[random_index], .metric = min_metric};
}

#endif
