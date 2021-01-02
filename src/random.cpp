#include "random.hpp"
#include <random>
#include <chrono>

auto random_int(int lower, int upper) -> int {
    static const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    static std::mt19937 random_generator(seed);
    std::uniform_int_distribution<> distribution(lower, upper);
    return distribution(random_generator);
}