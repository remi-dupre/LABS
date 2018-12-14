/* Try to localy increase the enery by reducing a targeted autocorrelation
 * coefficient.
 */
#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

#include "labs.hpp"
#include "optimizer.hpp"


class CorrMax : public Optimizer {
    public:
        using Optimizer::run;

        CorrMax(int seq_size, int seed, int nb_iter = 1000, int threshold = 1);

        Sequence run(LabsInstance& instance);
};
