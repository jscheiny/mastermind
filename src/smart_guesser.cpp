#include "console.hpp"
#include "match_table.hpp"
#include "scoped_timer.hpp"
#include "smart_guesser.hpp"
#include <algorithm>
#include <functional>
#include <future>
#include <random>
#include <sstream>

std::random_device random_device;
std::mt19937 random_generator(random_device());

auto smart_guesser::reset() -> void {
    guess_history_.clear();
    possible_secrets_ = secret_space{};
}

auto smart_guesser::update(int guess, match_value match) -> void {
    guess_history_.push_back(guess);
    possible_secrets_ = possible_secrets_.get_narrowed_space(guess, match);
}


auto smart_guesser::make_guess() const -> int {
    if (guess_history_.empty()) {
        std::uniform_int_distribution<> distribution(0, match_table::MAX_GUESS);
        return distribution(random_generator);
    }

    if (possible_secrets_.size() == 1) {
        return possible_secrets_[0];
    }

    static int threads = std::thread::hardware_concurrency();

    if (possible_secrets_.size() < threads) {
        return find_best_guess(1, 0).guess;
    }

    scoped_timer move_timer{"Make guess"};
    std::cout 
        << "Choosing among " 
        << console::green_fg 
        << possible_secrets_.size() 
        << console::reset 
        << " possible guesses" 
        << std::endl;
    std::vector<std::future<best_guess>> futures;

    for (int n = 0; n < threads; n++) {
        futures.push_back(
            std::async(std::launch::async, std::bind(&smart_guesser::find_best_guess, this, threads, n))
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

auto smart_guesser::find_best_guess(int threads, int offset) const -> best_guess {
    // std::stringstream ss;
    // ss << "Thread " << offset;
    // scoped_timer timer{ss.str()};
    int min_metric = std::numeric_limits<int>::max();
    std::vector<int> min_guesses;
    for (int index = offset; index < possible_secrets_.size(); index += threads) {
        int guess = possible_secrets_[index];
        int metric = evaluate_guess(guess);
        if (metric < min_metric) {
            min_metric = metric;
            min_guesses.clear();
            min_guesses.push_back(guess);
        } else if (metric == min_metric) {
            min_guesses.push_back(guess);
        }
    }

    std::uniform_int_distribution<> distribution(0, min_guesses.size() - 1);
    int random_index = distribution(random_generator);
    return {.guess = min_guesses[random_index], .metric = min_metric};
}

auto smart_guesser::evaluate_guess(int guess) const -> int {
    const auto& table = match_table::instance();
    int metric = 0;
    for (int secret : possible_secrets_) {
        match_value match = table.get_match(guess, secret);
        metric += possible_secrets_.get_narrowed_size(guess, match);
    }
    return metric;
}
