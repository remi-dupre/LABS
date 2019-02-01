/* Run through a decision tree trying to seek for a variety of local minimums.
 */
#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

#include "optimizer.hpp"


class LocalBranching : public Optimizer {
    public:
        using Optimizer::run;

        LocalBranching(int seq_size, int seed, int maximal_depth);

        Sequence run(LabsInstance& instance);

    private:
        double current_best_merit;
        Sequence current_best_seq;

        /* Browse the decision tree of swap each bit with a bounded account of
         * bad decisions
         */
        void browse_tree(
            LabsInstance& instance, const std::vector<size_t> &perm,
            int current_bit = 0, int current_depth = 0);
};

