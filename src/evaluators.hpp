#ifndef EVALUATORS_HPP
#define EVALUATORS_HPP

#include <vector>

auto average_narrowing(int guess, const std::vector<int>& search_space) -> int;
auto max_partition_size(int guess, const std::vector<int>& search_space) -> int;

#endif
