#ifndef UTILS_HPP
#define UTILS_HPP

#include "match_table.hpp"
#include <vector>
#include <numeric>

auto make_initial_search_space() -> std::vector<int> {
    std::vector<int> search_space(match_table::MAX_GUESS, 0);
    std::iota(search_space.begin(), search_space.end(), 0);
    return search_space;
}

#endif
