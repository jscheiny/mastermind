#include "console.hpp"
#include "mastermind.hpp"
#include "match_table.hpp"
#include "max_partition_size.hpp"
#include "parallelized_guesser.hpp"
#include "scoped_timer.hpp"
#include "secrets.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <stdlib.h>

auto main(int argc, char* argv[]) -> int {
    int games = atoi(argv[1]);

    match_table::instance();
    std::cout << std::endl;
    parallelized_guesser<max_partition_size> guesser{max_partition_size{}};

    std::vector<int> move_counts;
    {
        scoped_timer timer{"All games"};
        for (int i = 0; i < games; i++) {
            int moves = play_mastermind(guesser, random_secret());
            move_counts.push_back(moves);
            std::cout << "\nGame finished in " << console::red_fg << moves << console::reset << " moves\n" << std::endl;
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
