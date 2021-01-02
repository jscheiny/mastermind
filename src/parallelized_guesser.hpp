#ifndef PARALLELIZED_GUESSER_HPP
#define PARALLELIZED_GUESSER_HPP

#include "abstract_guesser.hpp"

class parallelized_guesser : public abstract_guesser {
public:
    virtual ~parallelized_guesser() {}

    virtual auto make_guess() const -> int override final;

protected:
    virtual auto should_guess_randomly() const -> bool;
    virtual auto evaluate_guess(int guess) const -> int = 0;

private:
    struct best_guess {
        int guess;
        int metric;
    };

    auto find_best_guess(int threads, int offset) const -> best_guess;

};

#endif
