#ifndef ABSTRACT_GUESSER_HPP
#define ABSTRACT_GUESSER_HPP

#include "match_value.hpp"

class abstract_guesser {
public:
    virtual ~abstract_guesser() {}

    virtual auto reset() -> void = 0;
    virtual auto make_guess() const -> int = 0;
    virtual auto update(int guess, match_value match) -> void = 0;
};

#endif
