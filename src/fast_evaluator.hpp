#ifndef FASTER_EVALUATOR_HPP
#define FASTER_EVALUATOR_HPP

#include "secret_space.hpp"

struct fast_evaluator {
    auto operator()(int guess, const secret_space& possible_secrets) const -> int;
};

#endif
