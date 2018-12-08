#include <iostream>
#include <random>

#include "labs.hpp"
#include "optimizer.hpp"
#include "corr_max.hpp"

using namespace std;


int main()
{
    random_device rd;

    ExampleOpt opt(300, rd());
    Sequence res = opt.run();

    for (int x : res) cout <<(x < 0 ? '-' : '+');

    cout << endl << merit(res) << endl;

    //

    CorrMax corr_max(300, rd());
    res = corr_max.run();

    for (int x : res) cout <<(x < 0 ? '-' : '+');

    cout << endl << merit(res) << endl;
}
