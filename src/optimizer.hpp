#pragma once

#include <random>

#include "labs.hpp"


/* Generic structure of an optimization algorithm.
 * Also encapsulate the random engine the algorithm should use.
 */
class Optimizer {
    public:
        Optimizer(int seq_size, int seed);

        /* Run the algorithm once and return the computed sequence */
        Sequence run();

        /* Run the algorithm using a specific LABS Instance to keep track of
         * requests */
        virtual Sequence run(LabsInstance& instance) = 0;

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
        using Optimizer::Optimizer;
        using Optimizer::run;

        Sequence run(LabsInstance& instance);
};
