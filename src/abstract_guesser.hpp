#ifndef ABSTRACT_GUESSER_HPP
#define ABSTRACT_GUESSER_HPP

#include "match_value.hpp"
#include <vector>

class abstract_guesser {
public:
    virtual ~abstract_guesser() {}

    virtual auto operator()(const std::vector<int>& guess_history, const std::vector<int>& search_space) const
        -> int = 0;
};

#endif
