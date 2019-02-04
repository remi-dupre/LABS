#include "simulated_annealing.hpp"


Simulated_Annealing::Simulated_Annealing(int seq_size, int seed, int nb_iter, double threshold) :
    Optimizer(seq_size, seed)
{
    name = "simulated_annealing";
    params = {
        {"seed", (int) seed},
        {"iterations", (int) nb_iter},
        {"threshold" , (double) threshold}
    };
}


Sequence Simulated_Annealing::run(LabsInstance& instance)
{
    srand (params["seed"]);
    Sequence seq = random_sequence();
    double seq_merit = instance.eval(seq);
    Sequence best_seq = seq;
    double best_merit = seq_merit;

    for (int step = 0 ; step < params["iterations"] ; step++) {
        int rand_bit = rand() % seq_size;
        Sequence new_seq = seq;
        new_seq[rand_bit] = -seq[rand_bit];
        double new_seq_merit = instance.eval(new_seq);

        if (new_seq_merit >= seq_merit ||
            (new_seq_merit >= seq_merit - params["threshold"] && step < params["iterations"]*0.75)){
            seq = new_seq;
            seq_merit = new_seq_merit;
        }
        if (seq_merit > best_merit){
            best_seq = seq;
            best_merit = seq_merit;
        }
    }
    return best_seq;
}
