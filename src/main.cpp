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

    /**
     * Comparing general performances between implementations
     */
    ostream << "{\n\t";
    serialize_json(ostream, "type", "compare");
    ostream << ",\n\t" << "\"dataset\": [\n\t\t";

    ExampleOpt(300, rd(), 10000).json_benchmark(ostream, false, "\t\t");
    ostream << ", ";
    CorrMax(300, rd(), 10000, 1).json_benchmark(ostream, false, "\t\t");
    ostream << ", ";
    CorrMax(300, rd(), 10000, 10).json_benchmark(ostream, false, "\t\t");
    ostream << ", ";
    CorrMax(300, rd(), 10000, 100).json_benchmark(ostream, false, "\t\t");

    ostream << "\n\t]\n}, ";

    /**
     * Testing performances when increasing dimention.
     */
    ostream << "{\n\t";
    serialize_json(ostream, "type", "benchmark");
    ostream << ",\n\t";
    serialize_json(ostream, "abciss", "dim");
    ostream << ",\n\t" << "\"dataset\": [\n\t\t";

    for (int n = 20 ; n <= 400 ; n += 20) {
        CorrMax(n, rd(), 5000, 1).json_benchmark(ostream, true, "\t\t");
        ostream << ", ";
        ExampleOpt(n, rd(), 5000).json_benchmark(ostream, true, "\t\t");

        if (n < 400)
            ostream << ", ";
    }

    ostream << "\n\t]\n},";

    /**
     * Testing performances when increasing threshold.
     */
    ostream << "{\n\t";
    serialize_json(ostream, "type", "benchmark");
    ostream << ",\n\t";
    serialize_json(ostream, "abciss", "threshold");
    ostream << ",\n\t" << "\"dataset\": [\n\t\t";

    for (int n = 1 ; n <= 1001 ; n += 50) {
        CorrMax(300, rd(), 5000, n).json_benchmark(ostream, true, "\t\t");
        if (n < 1000)
            ostream << ", ";
    }

    ostream << "\n\t]\n}";

    ostream << "]" << endl;
}
