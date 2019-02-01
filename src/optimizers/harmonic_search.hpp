/* Swap randomly bits over an entire period at once. In practice there is a
 * fair probability to get a period and offset that swap only few bits at once.
 * Thus it is still a local search variation.
 */
#pragma once

#include <algorithm>
#include <cassert>
#include <random>

#include "optimizer.hpp"


class HarmonicSearch : public Optimizer
{
    public:
        using Optimizer::run;

        HarmonicSearch(int seq_size, int seed, int nb_iterations);

        Sequence run(LabsInstance& instance);

    private:
        /**
         * Swap all bits of index period * i + offset of current sequence
         * (using local mode).
         */
        double swap_period(LabsInstance& instance, int period, int offset);
};

