#include "console.hpp"
#include "evaluators.hpp"
#include "mastermind.hpp"
#include "match_table.hpp"
#include "parallelized_guesser.hpp"
#include "scoped_timer.hpp"
#include "secrets.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdlib.h>

template<typename S>
auto simulate_games(int games, const S& score_fn, int threads = std::thread::hardware_concurrency()) -> void;

auto main(int argc, char* argv[]) -> int {
    if (argc < 1) {
        std::cout << "Error: Provide a number of games to play" << std::endl;
        return 1;
    }

    int games = atoi(argv[1]);

    match_table::initialize();

    simulate_games(games, average_block_size);
}

template<typename S>
auto simulate_games(int games, const S& score_fn, int threads) -> void {
    scoped_timer timer{"Games"};
    std::vector<std::future<int>> futures;
    int games_per_thread = games / threads;
    for (int i = 0; i < threads; i++) {
        futures.push_back(
            std::async(std::launch::async, [&score_fn, games_per_thread, threads]() {
                auto guesser = make_guesser(score_fn);
                int total_moves = 0;
                for (int i = 0; i < games_per_thread; i++) {
                    total_moves += play_mastermind(guesser, random_secret());
                }
                return total_moves;
            })
        );
    }

    int total_moves = 0;
    for (auto& future : futures) {
        total_moves += future.get();
    }

    double n = (double) games;
    double mean = total_moves / n;
    std::cout << "Average moves = " << console::green_fg << mean << console::reset << std::endl;
}
