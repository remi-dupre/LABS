#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#ifdef __linux__
    #include <sys/stat.h>
#endif

#include "labs.hpp"
#include "optimizer.hpp"
#include "corr_max.hpp"
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
                new ExampleOpt(300, seed, 10000),
                new CorrMax(300, seed, 10000, 1)
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
        }
    };

    for (int n = 20 ; n <= 400 ; n += 20) {
        tests[1].second.push_back(new CorrMax(n, seed, 5000, 1));
        tests[1].second.push_back(new ExampleOpt(n, seed, 5000));
    }

    for (int n = 1 ; n <= 1001 ; n += 50) {
        tests[2].second.push_back(new CorrMax(300, seed, 5000, n));
    }

    }

    run_output_tests(ostream, tests);
}
