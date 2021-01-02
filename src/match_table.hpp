#ifndef MATCH_TABLE_HPP
#define MATCH_TABLE_HPP

#include "match_value.hpp"
#include <vector>

class match_table {
public:
    static const int MAX_GUESS = 10000;

    static auto instance() -> const match_table&;

    auto get_match(int guess, int secret) const -> match_value;
private:
    std::vector<match_value> table_;

    match_table();
    auto read() -> bool;
    auto populate() -> void;
    auto write() const -> void;
    static auto get_index(int guess, int secret) -> int;
};

inline auto match_table::get_match(int guess, int secret) const -> match_value {
    return table_[get_index(guess, secret)];
}

inline auto match_table::get_index(int guess, int secret) -> int {
    return guess * match_table::MAX_GUESS + secret;
}


#endif 
