#include "match_table.hpp"
#include "match_value.hpp"
#include "secret_space.hpp"
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

auto check_secret(int secret, int guess, const match_value& match) -> bool;

secret_space::secret_space(): possible_secrets_(match_table::MAX_GUESS, 0) {
    std::iota(possible_secrets_.begin(), possible_secrets_.end(), 0);
}

auto secret_space::narrow(int guess, const match_value& match) -> void {
    std::vector<int> result;
    for (int secret : possible_secrets_) {
        if (check_secret(secret, guess, match)) {
            result.push_back(secret);
        }
    }
    possible_secrets_ = std::move(result);
}

auto secret_space::get_narrowed_size(int guess, const match_value& match) const -> int {
    int count = 0;
    for (int secret : possible_secrets_) {
        if (check_secret(secret, guess, match)) {
            count++;
        }
    }
    return count;
}

auto check_secret(int secret, int guess, const match_value& match) -> bool {
    const auto& table = match_table::instance();
    return table.get_match(guess, secret) == match && secret != guess;
}