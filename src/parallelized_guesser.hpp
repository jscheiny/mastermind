#ifndef PARALLELIZED_GUESSER_HPP
#define PARALLELIZED_GUESSER_HPP

#include "abstract_guesser.hpp"
#include "console.hpp"
#include "match_table.hpp"
#include "parallelized_guesser.hpp"
#include "random.hpp"
#include "scoped_timer.hpp"
#include <algorithm>
#include <functional>
#include <future>

template <typename E>
class parallelized_guesser : public abstract_guesser {
public:
    parallelized_guesser(
        E evaluate_guess,
        int threads = std::thread::hardware_concurrency()
    ): evaluate_guess_{evaluate_guess}, threads_{threads} {}

    virtual ~parallelized_guesser() {}

    virtual auto make_guess() const -> int override;

private:
    E evaluate_guess_;
    const int threads_;

    struct best_guess {
        int guess;
        int metric;
    };

    auto find_best_guess(int offset) const -> best_guess;
};

template <typename E>
auto parallelized_guesser<E>::make_guess() const -> int {
    scoped_timer move_timer{"Make guess"};
    std::cout 
        << "Choosing among " 
        << console::green_fg 
        << possible_secrets_.size() 
        << console::reset 
        << " possible guesses" 
        << std::endl;


    if (guess_history_.empty()) {
        return random_int(0, match_table::MAX_GUESS - 1);
    }

    if (possible_secrets_.size() == 1) {
        return possible_secrets_[0];
    }

    if (possible_secrets_.size() < threads_ || threads_ == 1) {
        return find_best_guess(0).guess;
    }

    std::vector<std::future<best_guess>> futures;

    for (int offset = 0; offset < threads_; offset++) {
        futures.push_back(
            std::async(
                std::launch::async, 
                std::bind(&parallelized_guesser::find_best_guess, this, offset)
            )
        );
    }

    std::vector<best_guess> results;
    for (auto& future : futures) {
        results.push_back(future.get());
    }

    std::random_shuffle(results.begin(), results.end());
    auto min = std::min_element(results.begin(), results.end(), [](best_guess a, best_guess b) { return a.metric < b.metric; });
    return min->guess;
}

template<typename E>
auto parallelized_guesser<E>::find_best_guess(int offset) const -> best_guess {
    int min_metric = std::numeric_limits<int>::max();
    std::vector<int> min_guesses;
    for (int index = offset; index < possible_secrets_.size(); index += threads_) {
        int guess = possible_secrets_[index];
        int metric = evaluate_guess_(guess, possible_secrets_);
        if (metric < min_metric) {
            min_metric = metric;
            min_guesses.clear();
            min_guesses.push_back(guess);
        } else if (metric == min_metric) {
            min_guesses.push_back(guess);
        }
    }

    int random_index = random_int(0, min_guesses.size() - 1);
    return {.guess = min_guesses[random_index], .metric = min_metric};
}

#endif
