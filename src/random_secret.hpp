#ifndef RANDOM_SECRET_HPP
#define RANDOM_SECRET_HPP

#include "abstract_secret.hpp"
#include "console.hpp"
#include "match_table.hpp"
#include "random.hpp"

class random_secret : public abstract_secret {
public:
    virtual ~random_secret() {}

    virtual auto reset() -> void override {
        secret_ = random_int(0, match_table::MAX_GUESS - 1);
        std::cout << "Secret: " << console::purple_fg << secret_ << console::reset << std::endl;
    }

    virtual auto check_guess(int guess) const -> match_value override {
        return match_table::instance().get_match(guess, secret_);
    }

private:
    int secret_;

};

#endif
