/* Try to localy increase the enery by reducing a targeted autocorrelation
 * coefficient.
 */
#pragma once

#include <algorithm>
#include <cmath>
#include <vector>
#include <utility>

#include "labs.hpp"
#include "optimizer.hpp"


class Genetic : public Optimizer {
    public:
        using Optimizer::run;

        Genetic(int seq_size, int seed, int nb_iter = 1000, int nb_parents = 100, int nb_childs = 1000);

        Sequence run(LabsInstance& instance);
};
