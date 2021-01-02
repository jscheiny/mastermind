#ifndef RANDOM_GUESSER_HPP
#define RANDOM_GUESSER_HPP

#include "abstract_guesser.hpp"
#include "secret_space.hpp"
#include <vector>

class smart_guesser : public abstract_guesser {
public:
    virtual ~smart_guesser() {}

    virtual auto reset() -> void override;
    virtual auto make_guess() const -> int override;
    virtual auto update(int guess, match_value match) -> void override;

private:
    std::vector<int> guess_history_;
    secret_space possible_secrets_;

    struct best_guess {
        int guess;
        int metric;
    };

    auto find_best_guess(int threads, int offset) const -> best_guess;
    auto evaluate_guess(int guess) const -> int;
};

#endif
