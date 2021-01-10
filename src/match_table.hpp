#ifndef MATCH_TABLE_HPP
#define MATCH_TABLE_HPP

#include "match_value.hpp"
#include <vector>

class match_table {
public:
    static const int MAX_GUESS = 10000;
    static auto initialize(bool in_memory) -> void;
    static auto get(int guess, int secret) -> match_value;

private:
    std::vector<match_value> table_;

    match_table(bool in_memory);
    auto read() -> bool;
    auto populate() -> void;
    auto write() const -> void;
    static auto instance(bool in_memory) -> const match_table&;
    static auto get_index(int guess, int secret) -> int;
};

inline auto match_table::initialize(bool in_memory) -> void {
    instance(in_memory);
}

inline auto match_table::instance(bool in_memory) -> const match_table& {
    static match_table table{in_memory};
    return table;
}

inline auto match_table::get(int guess, int secret) -> match_value {
    return instance(false).table_[get_index(guess, secret)];
}

inline auto match_table::get_index(int guess, int secret) -> int {
    return guess * match_table::MAX_GUESS + secret;
}


#endif 
