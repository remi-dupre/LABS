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
        using Optimizer::Optimizer;
        using Optimizer::run;

        Sequence run(LabsInstance& instance);
};
