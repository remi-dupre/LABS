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
                new Simulated_Annealing(300, seed, 100000, 1300),
                new Threshold_Localsearch(300, seed, 100000, 0.01),
                /*new LocalSearch(300, seed, 1000000, false),
                new LocalSearch(300, seed, 1000, true),
                new LocalBranching(300, seed, 1),
                new HarmonicSearch(300, seed, 50000),
                new ExampleOpt(300, seed, 10000),
                new CorrMax(300, seed, 10000, 1),
                new Genetic(300, seed, 300, 100, 300)*/
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
        tests[1].second.push_back(new Simulated_Annealing(n, seed, 100000, 1300));
        tests[1].second.push_back(new Threshold_Localsearch(n, seed, 100000, 0.01));

        /*tests[1].second.push_back(new CorrMax(n, seed, 5000, 1));
        tests[1].second.push_back(new ExampleOpt(n, seed, 5000));
        tests[1].second.push_back(new Simulated_Annealing(n, seed, 10000, 0.04));
        tests[1].second.push_back(new Genetic(n, seed, 100, 100, 300));
        //tests[1].second.push_back(new HarmonicSearch(n, seed, 50000));
        tests[1].second.push_back(new LocalBranching(n, seed, 1));
        //tests[1].second.push_back(new LocalSearch(n, seed, 1000, true));
        */
    }

    /*for (int i = 0.01; i <= 1; i+=0.01)
        tests[2].second.push_back(new Simulated_Annealing(300, seed, 1000, i));
        */
    run_output_tests(ostream, tests, 10);
}
