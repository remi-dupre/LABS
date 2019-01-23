/* Try to localy increase the enery by reducing a targeted autocorrelation
 * coefficient.
 */
#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include <utility>

#include "optimizer.hpp"


class Simulated_Annealing : public Optimizer {
    public:
        using Optimizer::run;

        Simulated_Annealing(int seq_size, int seed, int nb_iter = 3000, double threshold = 0.1);

        Sequence run(LabsInstance& instance);
};

