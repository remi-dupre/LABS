#include "simulated_annealing.hpp"


Simulated_Annealing::Simulated_Annealing(int seq_size, int seed, int nb_iter, double threshold) :
    Optimizer(seq_size, seed)
{
    name = "simulated_annealing";
    params = {
        {"iterations", (int) nb_iter},
        {"threshold" , (double) threshold}
    };
}


Sequence Simulated_Annealing::run(LabsInstance& instance)
{
    Sequence seq = random_sequence();
    double seq_merit = instance.init_local_mode(seq);
    Sequence best_seq = seq;
    double best_merit = seq_merit;

    for (int step = 0 ; step < params["iterations"] ; step++) {
        int rand_bit = rand() % seq_size;
        double new_seq_merit = instance.oracle_merit(rand_bit);

        if (new_seq_merit >= seq_merit ||
            (new_seq_merit >= seq_merit - params["threshold"] && step < params["iterations"]*0.75)){
            instance.swap_spin(rand_bit, true);
            seq_merit = new_seq_merit;
        }
        if (seq_merit > best_merit){
            best_seq = instance.local_checkpoint();
            best_merit = seq_merit;
        }
    }
    return best_seq;
}
