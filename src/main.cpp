#include <iostream>
#include <random>
#include <vector>

#include "labs.hpp"
#include "optimizer.hpp"
#include "corr_max.hpp"

using namespace std;


int main()
{
    random_device rd;

    cout << "[";
    ExampleOpt(300, rd(), 10000).json_benchmark();
    cout << ",\n";
    CorrMax(300, rd(), 10000, 1).json_benchmark();
    cout << ",\n";
    CorrMax(300, rd(), 10000, 10).json_benchmark();
    cout << ",\n";
    CorrMax(300, rd(), 10000, 100).json_benchmark();
    cout << "]" << endl;
}
