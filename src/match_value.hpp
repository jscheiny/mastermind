#ifndef MATCH_VALUE_HPP
#define MATCH_VALUE_HPP

#include <iostream>

class match_value {
public:
    match_value(): blacks_{0}, whites_{0} {}
    match_value(int b, int w): blacks_{b}, whites_{w} {}

    auto operator==(const match_value& other) const -> bool {
        return blacks_ == other.blacks_ && whites_ == other.whites_;
    }

    auto operator<(const match_value& other) const -> bool {
        if (blacks_ < other.blacks_) {
            return true;
        }
        if (blacks_ > other.blacks_) {
            return false;
        }
        return whites_ < other.whites_;
    }

    auto is_complete() const -> bool {
        return blacks_ == 4;
    }

    friend auto operator<< (std::ostream& os, const match_value& match) -> std::ostream&;

private:
    int blacks_;
    int whites_;
};

#endif
