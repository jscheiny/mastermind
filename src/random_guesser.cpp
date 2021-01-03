#include "match_table.hpp"
#include "random_guesser.hpp"
#include "random.hpp"

random_guesser::random_guesser(int free_guesses): free_guesses_{free_guesses} {}

auto random_guesser::operator()(
    const std::vector<int>& guess_history,
    const std::vector<int>& search_space
) const -> int {
    if (guess_history.size() < free_guesses_) {
        return random::index(match_table::MAX_GUESS);
    }

    int index = random::index(search_space.size());
    return search_space[index];
}
