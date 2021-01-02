#ifndef SMART_EVALUATOR_HPP
#define SMART_EVALUATOR_HPP

#include "secret_space.hpp"

struct smart_evaluator {
    auto operator()(int guess, const secret_space& possible_secrets) const -> int;
};

#endif
