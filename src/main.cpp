#include <iostream>

#include "labs.hpp"
#include "optimizer.hpp"

using namespace std;


int main()
{
    ExampleOpt opt(300, 0);
    Sequence res = opt.run();

    for (int x : res)
        cout << x << ' ';

    cout << endl << merit(res) << endl;
}
