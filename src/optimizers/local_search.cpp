#include "local_search.hpp"


LocalSearch::LocalSearch(int seq_size, int seed, int nb_iter) :
    Optimizer(seq_size, seed)
{
    name = "local_search";
    params = {
        {"iterations", (double) nb_iter}
    };
}

Sequence LocalSearch::run(LabsInstance& instance)
{
    std::uniform_int_distribution<int> rand_index(0, seq_size - 1);

    Sequence seq = random_sequence();
    double merit = instance.init_local_mode(seq);

    for (int i = 0 ; i < params["iterations"] ; i++) {
        const int k = rand_index(random_engine);
        const double new_merit = instance.oracle_merit(k);

        if (new_merit > merit)
            merit = new_merit;

        seq = instance.swap_spin(k);
    }

    return seq;
}

