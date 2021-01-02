#ifndef RANDOM_SECRET_HPP
#define RANDOM_SECRET_HPP

#include "abstract_secret.hpp"
#include "match_table.hpp"
#include <random>

class random_secret : public abstract_secret {
public:
    virtual ~random_secret() {}

    virtual auto reset() -> void override {
        static std::random_device random_device;
        static std::mt19937 random_generator(random_device());
        static std::uniform_int_distribution<> distribution(0, match_table::MAX_GUESS - 1);
        secret_ = distribution(random_generator);
    }

    virtual auto check_guess(int guess) const -> match_value override {
        return match_table::instance().get_match(guess, secret_);
    }

private:
    int secret_;

};

#endif
