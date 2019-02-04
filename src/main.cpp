#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#ifdef __linux__
    #include <sys/stat.h>
#endif

#include "run_tests.hpp"

using namespace std;


int main()
{
    #ifdef __linux__
        mkdir("data", 0755);
    #endif

    // Open log files
    std::ofstream ostream("./data/tests.json", std::ios::trunc);

    // Start testing
    random_device rd;
    const auto seed = rd();

    std::vector<Test> tests = {
        // General purpose tests
        {
            {
                {"type", "compare"},
                {"with_history", "yes"}
            },
            {
                new HarmonicSearch(300, seed, 50000),
                new LocalBranching(300, seed, 1),
                new LocalSearch(300, seed, 1000, true),
                new ExampleOpt(300, seed, 10000),
                new CorrMax(300, seed, 10000, 1),
                new Simulated_Annealing(300, seed, 10000, 0.013)
                new Genetic(300, seed, 300, 1000, 3000)
            }
        },
        // Increasing dimention
        {
            {
                {"type", "benchmark"},
                {"abciss", "dim"}
            },
            {}
        },
        // Increasing threshold
        {
            {
                {"type", "benchmark"},
                {"abciss", "threshold"}
            },
            {}
        },
        {
            {
                {"type", "benchmark"},
                {"abciss", "nb_parents"}
            },
            {}
        },
        {
            {
                {"type", "benchmark"},
                {"abciss", "threshold"}
            },
            {}
        }

    };

    for (int n = 20 ; n <= 400 ; n += 20) {
        tests[1].second.push_back(new CorrMax(n, seed, 5000, 1));
        tests[1].second.push_back(new ExampleOpt(n, seed, 5000));
        tests[1].second.push_back(new Simulated_Annealing(n, seed, 5000, 0.013));
        tests[1].second.push_back(new Genetic(n, seed, 100, 300, 3000));
    }

    /*

    for (int n = 1 ; n <= 1001 ; n += 50) {
        tests[2].second.push_back(new CorrMax(300, seed, 5000, n));
    }

    for (int n = 100 ; n <= 1500 ; n += 100) {
        tests[3].second.push_back(new Genetic(300, seed, 100, n, 3000));
    }
    */
    for (int n = 500 ; n >= 20 ; n -= 10) {
        tests[4].second.push_back(new  Simulated_Annealing(300, seed, 5000, (double) 1/n));
    }

    run_output_tests(ostream, tests, 10);
}

