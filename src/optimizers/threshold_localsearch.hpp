/* Try to localy increase the enery by reducing a targeted autocorrelation
 * coefficient.
 */
#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include <utility>

#include "optimizer.hpp"


class Threshold_Localsearch : public Optimizer {
    public:
        using Optimizer::run;

        Threshold_Localsearch(int seq_size, int seed, int nb_iter = 3000,
            double threshold = 0.01);

        Sequence run(LabsInstance& instance);
};
