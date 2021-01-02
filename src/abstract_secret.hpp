#ifndef ABSTRACT_SECRET_HPP
#define ABSTRACT_SECRET_HPP

#include "match_value.hpp"

class abstract_secret {
public:
    virtual ~abstract_secret() {}

    virtual auto reset() -> void = 0;
    virtual auto check_guess(int guess) const -> match_value = 0;
};

#endif
