#ifndef SMART_EVALUATOR_HPP
#define SMART_EVALUATOR_HPP

#include <vector>

struct smart_evaluator {
    auto operator()(int guess, const std::vector<int>& possible_secrets) const -> int;
};

#endif
