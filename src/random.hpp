#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <chrono>
#include <random>

class random {
public:
    static auto range(int lower, int upper) -> int;

    template<typename T>
    static auto shuffle(T begin, T end) -> void;

private:
    static std::mt19937 random_generator;

};

template<typename T>
auto random::shuffle(T begin, T end) -> void {
    std::shuffle(begin, end, random_generator);
}

#endif
