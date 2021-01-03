#include "evaluators.hpp"
#include "match_table.hpp"
#include <algorithm>
#include <map>

auto partition_search_space(int guess, const std::vector<int>& search_space) -> std::map<match_value, int>;

auto average_narrowing(int guess, const std::vector<int>& search_space) -> int {
    const auto& table = match_table::instance();
    auto partitions = partition_search_space(guess, search_space);
    int metric = 0;
    for (int secret : search_space) {
        match_value match = table.get_match(guess, secret);
        metric += partitions[match];
    }
    return metric;
}

auto max_partition_size(int guess, const std::vector<int>& search_space) -> int {
    auto partitions = partition_search_space(guess, search_space);
    int max_partition_size = -1;
    for (const auto& entry : partitions) {
        max_partition_size = std::max(entry.second, max_partition_size);
    }

    return max_partition_size;
}

auto partition_search_space(int guess, const std::vector<int>& search_space) -> std::map<match_value, int> {
    const auto& table = match_table::instance();
    std::map<match_value, int> partitions;
    for (int secret : search_space) {
        match_value match = table.get_match(guess, secret);
        partitions[match]++;
    }
    return partitions;
}