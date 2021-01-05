#ifndef SCORE_FUNCTIONS_HPP
#define SCORE_FUNCTIONS_HPP

#include "console.hpp"
#include <iostream>
#include <vector>

auto average_block_size(int guess, const std::vector<int>& search_space) -> int;
auto max_block_size(int guess, const std::vector<int>& search_space) -> int;

template<typename A, typename B>
auto compare_score_functions(A score_fn_a, B score_fn_b) {
    return [score_fn_a, score_fn_b](int guess, const std::vector<int>& search_space) -> int {
        int score_a = score_fn_a(guess, search_space);
        int score_b = score_fn_b(guess, search_space);
        if (score_a != score_b) {
            std::cout << "Scores are not the same "<< std::endl;
        }
        return result_a;
    };
}

#endif
