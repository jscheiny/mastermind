#include "mastermind.hpp"
#include "match_table.hpp"
#include "score_functions.hpp"
#include "scored_guesser.hpp"
#include "secrets.hpp"
#include <iostream>
#include <future>

template<typename S>
auto simulate_games(int games, const S& score_fn, int full_space_guesses, int threads = std::thread::hardware_concurrency()) -> void;

auto main(int argc, char* argv[]) -> int {
    if (argc < 1) {
        std::cout << "Error: Provide a number of games to play" << std::endl;
        return 1;
    }

    int games = atoi(argv[1]);

    match_table::initialize(true);

    for (int full_space_guesses = 1; full_space_guesses < 7; full_space_guesses++) {
        simulate_games(games, average_block_size, full_space_guesses);
    }
}

template<typename S>
auto simulate_games(int games, const S& score_fn, int full_space_guesses, int threads) -> void {
    std::vector<std::future<int>> futures;
    int games_per_thread = games / threads;
    int mod = games % threads;
    for (int thread = 0; thread < threads; thread++) {
        futures.push_back(
            std::async(std::launch::async, [&score_fn, full_space_guesses, games_per_thread, mod, thread, threads]() {
                auto guesser = make_scored_guesser(score_fn, full_space_guesses);
                int moves = 0;
                int games = thread < mod ? games_per_thread + 1 : games_per_thread;
                for (int i = 0; i < games_per_thread; i++) {
                    moves += play_mastermind(guesser, random_secret());
                }
                return moves;
            })
        );
    }

    double total_games = (double) games;
    int total_moves = 0;
    for (auto& future : futures) {
        total_moves += future.get();
    }

    double mean = total_moves / total_games;
    std::cout << "\nResult of " << games << " games with " << full_space_guesses << " full space guesses" << std::endl;
    std::cout << "Average moves = " << mean << std::endl;
}
