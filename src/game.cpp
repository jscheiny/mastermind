#include "console.hpp"
#include "game.hpp"
#include "match_table.hpp"
#include "scoped_timer.hpp"
#include <vector>
#include <numeric>

auto get_initial_search_space() -> std::vector<int>;
auto narrow_search_space(const std::vector<int>& search_space, int guess, const match_value& match) -> std::vector<int>;

auto game::play() -> int {
    int moves = 0;
    secret_->reset();
    scoped_timer game_timer{"Game"};
    std::vector<int> guess_history;
    std::vector<int> search_space = get_initial_search_space();
    while (true) {
        int guess = (*guesser_)(guess_history, search_space);
        guess_history.push_back(guess);
        match_value match = secret_->check_guess(guess);
        moves++;
        if (match.is_complete()) {
            break;
        }
        search_space = narrow_search_space(search_space, guess, match);
    }
    
    std::cout << "Guesses";
    for (int guess : guess_history) {
        std::cout << " -> " << console::purple_fg << guess << console::reset;
    }
    std::cout << std::endl;

    return moves;
}

auto get_initial_search_space() -> std::vector<int> {
    std::vector<int> search_space(match_table::MAX_GUESS, 0);
    std::iota(search_space.begin(), search_space.end(), 0);
    return search_space;
}

auto narrow_search_space(const std::vector<int>& search_space, int guess, const match_value& match) -> std::vector<int> {
    const auto& table = match_table::instance();
    std::vector<int> new_search_space;
    for (int secret : search_space) {
        if (table.get_match(guess, secret) == match && secret != guess) {
            new_search_space.push_back(secret);
        }
    }
    return new_search_space;
}
