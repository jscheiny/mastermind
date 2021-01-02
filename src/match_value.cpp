#include "match_value.hpp"
#include <iostream>

auto operator<< (std::ostream& os, const match_value& result) -> std::ostream& {
    return os << result.blacks_ << " " << result.whites_;
}
