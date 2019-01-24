/**
 * Randomly walks over the space spining only one bit at once.
 */
#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "optimizer.hpp"


class LocalSearch : public Optimizer {
    public:
        using Optimizer::run;

        LocalSearch(int seq_size, int seed, int nb_iter = 1000);

        Sequence run(LabsInstance& instance);
};
