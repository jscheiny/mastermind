#ifndef FIXED_SECRET_HPP
#define FIXED_SECRET_HPP

#include "abstract_secret.hpp"
#include "match_table.hpp"

class fixed_secret : public abstract_secret {
public:
    fixed_secret(int secret): secret_{secret} {}
    virtual ~fixed_secret() {}

    virtual auto reset() -> void override {}

    virtual auto check_guess(int guess) const -> match_value override {
        return match_table::instance().get_match(guess, secret_);
    }

private:
    int secret_;
};

#endif
