#ifndef ABSTRACT_GUESSER_HPP
#define ABSTRACT_GUESSER_HPP

#include "match_value.hpp"
#include <vector>

class abstract_guesser {
public:
    virtual ~abstract_guesser() {}

    virtual auto make_guess() const -> int = 0;

    auto reset() -> void;
    auto update(int guess, match_value match) -> void;
    
protected:
    std::vector<int> guess_history_;
    std::vector<int> search_space_;

};

#endif
