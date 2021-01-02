#ifndef SCOPED_TIMER_HPP
#define SCOPED_TIMER_HPP

#include <chrono>
#include <string>

class scoped_timer {
public:
    scoped_timer(const std::string& name);
    ~scoped_timer();

private:
    std::string name_;
    decltype(std::chrono::high_resolution_clock::now()) start_;  
};

#endif
