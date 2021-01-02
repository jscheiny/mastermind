#ifndef RANDOM_GUESSER_HPP
#define RANDOM_GUESSER_HPP

#include "parallelized_guesser.hpp"

class smart_guesser : public parallelized_guesser {
public:
    virtual ~smart_guesser() {}

protected:
    auto evaluate_guess(int guess) const -> int;
};

#endif
