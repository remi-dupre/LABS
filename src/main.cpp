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

    ostream << "[";
    ExampleOpt(300, rd(), 10000).json_benchmark(ostream);
    ostream << ",\n";
    CorrMax(300, rd(), 10000, 1).json_benchmark(ostream);
    ostream << ",\n";
    CorrMax(300, rd(), 10000, 10).json_benchmark(ostream);
    ostream << ",\n";
    CorrMax(300, rd(), 10000, 100).json_benchmark(ostream);
    ostream << "]" << endl;
}
