#ifndef FASTER_EVALUATOR_HPP
#define FASTER_EVALUATOR_HPP

#include <vector>

struct max_partition_size {
    auto operator()(int guess, const std::vector<int>& search_space) const -> int;
};

#endif
