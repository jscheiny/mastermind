#ifndef AVERAGE_NARROWING_HPP
#define AVERAGE_NARROWING_HPP

#include <vector>

struct average_narrowing {
    auto operator()(int guess, const std::vector<int>& search_space) const -> int;
};

#endif
