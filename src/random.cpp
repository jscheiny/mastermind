#include "random.hpp"
#include <random>
#include <chrono>

std::mt19937 random::random_generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());

auto random::range(int lower, int upper) -> int {
    std::uniform_int_distribution<> distribution(lower, upper);
    return distribution(random_generator);
}

auto random::index(int size) -> int {
    return range(0, size - 1);
}
