#include "match_table.hpp"
#include "match_value.hpp"
#include "scoped_timer.hpp"
#include <fstream>

auto compute_match(int guess, int secret) -> match_value;
auto digits(int guess) -> std::string;

static const std::string TABLE_PATH = "match_table.txt";

auto match_table::instance() -> const match_table& {
    static match_table table;
    return table;
}

match_table::match_table(): table_ {MAX_GUESS * MAX_GUESS} {
    auto can_read_table = read();
    if (!can_read_table) {
        populate();
        write();
    }
}

auto match_table::read() -> bool {
    std::ifstream file{TABLE_PATH};
    if (!file.good()) {
        return false;
    }
    
    scoped_timer read_timer{"Read match table"};
    int blacks, whites;
    int index = 0;
    while (file >> blacks >> whites) {
        table_[index] = { blacks, whites };
        index++;
    }
    return true;
}

auto match_table::populate() -> void {
    for (int guess = 0; guess < match_table::MAX_GUESS; guess++) {
        for (int secret = 0; secret <= guess; secret++) {
            auto match = compute_match(guess, secret);
            table_[get_index(guess, secret)] = match;
            table_[get_index(secret, guess)] = match;
        }
    }
}

auto match_table::write() const -> void {
    std::ofstream file{TABLE_PATH};
    for (int index = 0; index < table_.size(); index++) {
        auto guess = table_[index];
        file << guess << "\n";
    }
}

auto compute_match(int guess, int secret) -> match_value {
    int blacks = 0;
    int whites = 0;
    auto guess_str = digits(guess);
    auto secret_str = digits(secret);

    bool index_has_black[4] = {false, false, false, false};

    for (int index = 0; index < 4; index++) {
        if (guess_str[index] == secret_str[index]) {
            blacks++;
            index_has_black[index] = true;
        }
    }


    int guess_digit_histogram[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int secret_digit_histogram[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int index = 0; index < 4; index++) {
        if (index_has_black[index]) {
            continue;
        }

        int guess_digit = guess_str[index] - '0';
        int secret_digit = secret_str[index] - '0';
        guess_digit_histogram[guess_digit]++;
        secret_digit_histogram[secret_digit]++;
    }

    for (int digit = 0; digit <= 9; digit++) {
        whites += std::min(guess_digit_histogram[digit], secret_digit_histogram[digit]);
    }

    return { blacks, whites };
}

auto digits(int guess) -> std::string {
    auto guess_str = std::to_string(guess);
    while (guess_str.size() < 4) {
        guess_str = "0" + guess_str;
    }
    return guess_str;
}