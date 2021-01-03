#include "average_narrowing.hpp"
#include "match_table.hpp"
#include <map>

auto average_narrowing(int guess, const std::vector<int>& search_space) -> int {
    const auto& table = match_table::instance();
    std::map<match_value, int> partitions;
    for (int secret : search_space) {
        match_value match = table.get_match(guess, secret);
        partitions[match]++;
    }

    int metric = 0;
    for (int secret : search_space) {
        match_value match = table.get_match(guess, secret);
        metric += partitions[match];
    }
    return metric;
}
