#include "console.hpp"
#include "game.hpp"
#include "scoped_timer.hpp"
#include <vector>

auto game::play() -> int {
    int moves = 0;
    guesser_->reset();
    secret_->reset();
    scoped_timer game_timer{"Game"};
    std::vector<int> guesses;
    while (true) {
        int guess = guesser_->make_guess();
        guesses.push_back(guess);
        moves++;
        match_value match = secret_->check_guess(guess);
        if (match.is_complete()) {
            break;
        }
        guesser_->update(guess, match);
    }
    
    std::cout << "Guesses";
    for (int guess : guesses) {
        std::cout << " -> " << console::purple_fg << guess << console::reset;
    }
    std::cout << std::endl;

    return moves;
}