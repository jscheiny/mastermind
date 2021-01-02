#include "abstract_guesser.hpp"
#include "secret_space.hpp"

auto abstract_guesser::reset() -> void {
    guess_history_.clear();
    possible_secrets_ = secret_space{};
}

auto abstract_guesser::update(int guess, match_value match) -> void {
    guess_history_.push_back(guess);
    possible_secrets_.narrow(guess, match);
}
