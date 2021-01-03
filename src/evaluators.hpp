#ifndef EVALUATORS_HPP
#define EVALUATORS_HPP

#include "console.hpp"
#include <iostream>
#include <vector>

auto average_block_size(int guess, const std::vector<int>& search_space) -> int;
auto max_block_size(int guess, const std::vector<int>& search_space) -> int;

template<typename A, typename B>
auto compare_evaluators(A evaluator_a, B evaluator_b) {
    return [evaluator_a, evaluator_b](int guess, const std::vector<int>& search_space) -> int {
        int result_a = evaluator_a(guess, search_space);
        int result_b = evaluator_b(guess, search_space);
        if (result_a != result_b) {
            std::cout << "Evaluators are not the same "<< std::endl;
        }
        return result_a;
    };
}

#endif
