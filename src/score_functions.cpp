#include "match_table.hpp"
#include "score_functions.hpp"
#include <algorithm>
#include <map>
#include <sstream>

auto get_block_sizes(int guess, const std::vector<int>& search_space) -> std::vector<int>;
auto get_block_index(const match_value& match) -> int;
static const int MAX_BLOCK_INDEX = 16;

auto average_block_size(int guess, const std::vector<int>& search_space) -> int {
    auto block_sizes = get_block_sizes(guess, search_space);
    int metric = 0;
    for (const auto& size : block_sizes) {
        metric += size * size;
    }

    return metric;
}

auto max_block_size(int guess, const std::vector<int>& search_space) -> int {
    auto block_sizes = get_block_sizes(guess, search_space);
    int max_block_size = -1;
    for (const auto& size : block_sizes) {
        max_block_size = std::max(size, max_block_size);
    }

    return max_block_size;
}

auto get_block_sizes(int guess, const std::vector<int>& search_space) -> std::vector<int> {
    std::vector<int> block_sizes(MAX_BLOCK_INDEX + 1, 0);
    for (int secret : search_space) {
        match_value match = match_table::get(guess, secret);
        block_sizes[get_block_index(match)]++;
    }
    return block_sizes;
}

auto get_block_index(const match_value& match) -> int {
    return match.blacks() * 4 + match.whites();
}