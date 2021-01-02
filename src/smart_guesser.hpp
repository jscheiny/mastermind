#ifndef RANDOM_GUESSER_HPP
#define RANDOM_GUESSER_HPP

#include "abstract_guesser.hpp"
#include "secret_space.hpp"
#include <vector>

class smart_guesser : public abstract_guesser {
public:
    virtual ~smart_guesser() {}

    virtual auto make_guess() const -> int override;

private:
    struct best_guess {
        int guess;
        int metric;
    };

    auto find_best_guess(int threads, int offset) const -> best_guess;
    auto evaluate_guess(int guess) const -> int;
};

#endif
