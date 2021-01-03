#ifndef GAME_HPP
#define GAME_HPP

#include "match_table.hpp"
#include "scoped_timer.hpp"
#include <chrono>
#include <memory>
#include <vector>
#include <numeric>

template<typename Guesser, typename Secret>
auto play_game(Guesser guesser, Secret secret) -> int;

template<typename Guesser, typename Secret>
class game {
public:
    game(Guesser guesser, Secret secret);

    auto play() -> int;
private:
    Guesser guesser_;
    Secret secret_;
    std::vector<int> guess_history_;
    std::vector<int> search_space_;

    auto narrow_search_space(int guess, const match_value& match) -> void;
};


template<typename Guesser, typename Secret>
auto play_game(Guesser guesser, Secret secret) -> int {
    return game<Guesser, Secret>{guesser, secret}.play();
}

template<typename Guesser, typename Secret>
game<Guesser, Secret>::game(Guesser guesser, Secret secret): guesser_{guesser}, secret_{secret} {
    search_space_ = std::vector<int>(match_table::MAX_GUESS, 0);
    std::iota(search_space_.begin(), search_space_.end(), 0);
}

template<typename Guesser, typename Secret>
auto game<Guesser, Secret>::play() -> int {
    int moves = 0;
    scoped_timer game_timer{"Game"};
    while (true) {
        int guess = guesser_(guess_history_, search_space_);
        guess_history_.push_back(guess);
        match_value match = secret_(guess);
        moves++;
        if (match.is_complete()) {
            break;
        }
        narrow_search_space(guess, match);
    }
    
    std::cout << "Guesses";
    for (int guess : guess_history_) {
        std::cout << " -> " << console::purple_fg << guess << console::reset;
    }
    std::cout << std::endl;

    return moves;
}

template<typename Guesser, typename Secret>
auto game<Guesser, Secret>::narrow_search_space(int guess, const match_value& match) -> void {
    const auto& table = match_table::instance();
    std::vector<int> new_search_space;
    for (int secret : search_space_) {
        if (table.get_match(guess, secret) == match && secret != guess) {
            new_search_space.push_back(secret);
        }
    }
    search_space_ = new_search_space;
}

#endif