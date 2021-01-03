#ifndef RANDOM_GUESSER_HPP
#define RANDOM_GUESSER_HPP

#include <vector>

class random_guesser {
public:
    random_guesser(int free_guesses);

    auto operator()(const std::vector<int>& guess_history, const std::vector<int>& search_space) const -> int;

private:
    int free_guesses_;
};

#endif
