#include "scoped_timer.hpp"
#include <iostream>

scoped_timer::scoped_timer(const std::string& name): name_{name}, start_{std::chrono::high_resolution_clock::now()} {}

scoped_timer::~scoped_timer() {
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start_);
    const double seconds = duration.count() / 1000.0;
    std::cout
        << "["
        << name_
        << " finished in "
        << seconds
        << "s]"
        << std::endl;
}
