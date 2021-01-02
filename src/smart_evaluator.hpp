#ifndef SMART_EVALUATOR_HPP
#define SMART_EVALUATOR_HPP

#include <vector>

struct smart_evaluator {
    auto operator()(int guess, const std::vector<int>& search_space) const -> int;
};

#endif
