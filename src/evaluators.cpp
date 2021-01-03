#include "evaluators.hpp"
#include "match_table.hpp"
#include <algorithm>
#include <map>

auto get_block_sizes(int guess, const std::vector<int>& search_space) -> std::map<match_value, int>;

auto average_block_size(int guess, const std::vector<int>& search_space) -> int {
    auto block_sizes = get_block_sizes(guess, search_space);
    int metric = 0;
    for (const auto& entry : block_sizes) {
        metric += entry.second * entry.second;
    }

    return metric;
}

auto max_block_size(int guess, const std::vector<int>& search_space) -> int {
    auto block_sizes = get_block_sizes(guess, search_space);
    int max_block_size = -1;
    for (const auto& entry : block_sizes) {
        max_block_size = std::max(entry.second, max_block_size);
    }

    return max_block_size;
}

auto get_block_sizes(int guess, const std::vector<int>& search_space) -> std::map<match_value, int> {
    std::map<match_value, int> block_sizes;
    for (int secret : search_space) {
        match_value match = match_table::get(guess, secret);
        block_sizes[match]++;
    }
    return block_sizes;
}
