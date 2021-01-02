#include "fast_evaluator.hpp"
#include "match_table.hpp"
#include <map>
#include <algorithm>

auto fast_evaluator::operator()(int guess, const std::vector<int>& search_space) const -> int {
    const auto& table = match_table::instance();
    std::map<match_value, int> partitions;
    for (int secret : search_space) {
        match_value match = table.get_match(guess, secret);
        partitions[match]++;
    }

    int max_partition_size = -1;
    for (const auto& entry : partitions) {
        max_partition_size = std::max(entry.second, max_partition_size);
    }

    return max_partition_size;
}