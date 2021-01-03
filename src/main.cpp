#include "average_narrowing.hpp"
#include "console.hpp"
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

auto main(int argc, char* argv[]) -> int {
    if (argc < 1) {
        std::cout << "Error: Provide a number of games to play" << std::endl;
        return 1;
    }

    int games = atoi(argv[1]);

    match_table::instance();

    auto guesser = make_parallelized_guesser(average_narrowing{});
    std::vector<int> move_counts;
    {
        std::stringstream timer_name;
        timer_name << games << " games";
        scoped_timer timer{timer_name.str()};
        for (int i = 0; i < games; i++) {
            int moves = play_mastermind(guesser, random_secret());
            move_counts.push_back(moves);
        }   
    }

    int sum = std::accumulate(move_counts.begin(), move_counts.end(), 0);
    double n = (double) games;
    double mean = sum / n;
    double total_deviation = 0;
    for (int count : move_counts) {
        int deviation = count - mean;
        total_deviation += deviation * deviation;
    }
    double variance = total_deviation / n;
    double stddev = sqrt(variance);

    std::cout << "\nAverage moves = " << console::green_fg << mean << console::reset << std::endl;
    std::cout << "Standard deviation = " << console::green_fg << stddev << console::reset << std::endl;
}
