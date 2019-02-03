#pragma once

#include <cassert>
#include <chrono>
#include <iostream>
#include <map>
#include <random>
#include <string>

#include "../json.hpp"
#include "../labs.hpp"


/* Generic structure of an optimization algorithm.
 * Also encapsulate the random engine the algorithm should use.
 */
class Optimizer {
    public:
        /* Name of the algorithm */
        std::string name = "unnamed";

        /* Extra parameters for the algorithm */
        std::map<std::string, double> params;

        Optimizer(int seq_size, int seed);

        /* Run the algorithm once and return the computed sequence */
        Sequence run();

        /* Run the algorithm using a specific LABS Instance to keep track of
         * requests */
        virtual Sequence run(LabsInstance& instance) = 0;

        /* Test routines */
        void json_benchmark(std::ostream& stream, bool light = false,
            int nb_tests = 1, const std::string& line_prefix = "");

    protected:

        /* Return a random sequence according to uniform distribution */
        Sequence random_sequence();

        int seq_size;  // size of sequences generated
        std::default_random_engine random_engine;  // for randomization
};


/* Example on how to use the Optimizer class.
 * The only method that needs to be overloaded is run(LabsInstance&).
 */
class ExampleOpt : public Optimizer {
    public:
        using Optimizer::run;

        ExampleOpt(int seq_size, int seed, int nb_iter = 10000);

        Sequence run(LabsInstance& instance);

    private:
};

