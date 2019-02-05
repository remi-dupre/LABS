#include "local_branching.hpp"


LocalBranching::LocalBranching(int seq_size, int seed, int maximal_depth) :
    Optimizer(seq_size, seed)
{
    assert(maximal_depth >= 0);

    name = "local_branching";
    params = {
        {"maximal_depth", maximal_depth}
    };
}

Sequence LocalBranching::run(LabsInstance& instance)
{
    current_best_seq = random_sequence();
    current_best_merit = instance.init_local_mode(current_best_seq);

    std::vector<size_t> perm(seq_size);

    for (int i = 0 ; i < seq_size ; i++)
        perm[i] = i;

    std::shuffle(perm.begin(), perm.end(), random_engine);
    browse_tree(instance, perm);

    return current_best_seq;
}

void LocalBranching::browse_tree(LabsInstance& instance,
    const std::vector<size_t> &perm, int current_bit, int current_depth)
{
    if (current_bit >= seq_size) {
        instance.local_checkpoint();
        return;
    }

    const int maximal_depth = params["maximal_depth"];

    const double noswap_merit = instance.oracle_merit();
    const double wtswap_merit = instance.swap_spin(current_bit, false);

    if (wtswap_merit > noswap_merit || current_depth < maximal_depth) {
        bool cheating = wtswap_merit <= noswap_merit;
        browse_tree(instance, perm, current_bit + 1, current_depth + cheating);
    }

    instance.swap_spin(current_bit, false);

    if (wtswap_merit < noswap_merit || current_depth < maximal_depth) {
        bool cheating = wtswap_merit >= noswap_merit;
        browse_tree(instance, perm, current_bit + 1, current_depth + cheating);
    }

    if (noswap_merit > current_best_merit) {
        current_best_merit = noswap_merit;
        current_best_seq = instance.local_checkpoint();
    }
}

