#include "local_search.hpp"


LocalSearch::LocalSearch(int seq_size, int seed, int nb_iterations,
        bool seek_local_maximum) :
    Optimizer(seq_size, seed)
{
    name = "local_search";
    params = {
        {"nb_iterations", (double) nb_iterations},
        {"seek_local_maximum", (double) seek_local_maximum}
    };
}

Sequence LocalSearch::run(LabsInstance& instance)
{
    const int nb_iterations = params["nb_iterations"];
    const bool seek_local_maximum = params["seek_local_maximum"];

    std::uniform_int_distribution<int> rand_index(0, seq_size - 1);


    Sequence seq = random_sequence();
    double merit = instance.init_local_mode(seq);

    for (int i = 0 ; i < nb_iterations ; i++) {
        const int k = rand_index(random_engine);
        double new_merit = instance.swap_spin(k, false);

        // Seek for local maximum
        if (seek_local_maximum) {
            bool go_on;

            do {
                go_on = false;

                for (int k = 0; k < seq_size ; k++) {
                    if (instance.oracle_merit(k) > new_merit) {
                        new_merit = instance.swap_spin(k, true);
                        go_on = true;
                        break;
                    }
                }
            } while(go_on);
        }

        if (new_merit > merit) {
            seq = instance.local_checkpoint();
            merit = new_merit;
        }
    }

    return seq;
}

