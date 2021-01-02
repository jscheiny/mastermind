#ifndef GAME_HPP
#define GAME_HPP

#include "abstract_guesser.hpp"
#include "abstract_secret.hpp"
#include <chrono>
#include <memory>

class game {
public:
    game(
        std::shared_ptr<abstract_guesser> guesser,
        std::shared_ptr<abstract_secret> secret
    ): guesser_{guesser}, secret_{secret} {}

    auto play() -> int;
private:
    std::shared_ptr<abstract_guesser> guesser_;
    std::shared_ptr<abstract_secret> secret_;
};

#endif