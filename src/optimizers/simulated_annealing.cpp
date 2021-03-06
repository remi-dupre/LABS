#include "simulated_annealing.hpp"


Simulated_Annealing::Simulated_Annealing(int seq_size, int seed, int nb_iter, int temperature) :
    Optimizer(seq_size, seed)
{
    name = "simulated_annealing";
    params = {
        {"iterations", (int) nb_iter},
        {"temperature" , (double) temperature}
    };
}


Sequence Simulated_Annealing::run(LabsInstance& instance)
{
    Sequence seq = random_sequence();
    double seq_merit = instance.init_local_mode(seq);
    Sequence best_seq = seq;
    double best_merit = seq_merit;
    double T = params["temperature"];
    double temperature_decrease_coef = 0.95;
    int N = seq_size;

    for (int step = 0 ; step < params["iterations"] ; step++) {
        if (step%50000)  T = temperature_decrease_coef*T;
        int rand_bit = rand() % seq_size;
        double new_seq_merit = instance.oracle_merit(rand_bit);
        double r = ((double) rand() / (RAND_MAX));
        double E_seq = (N*N)/(2*seq_merit);
        double E_new_seq = (N*N)/(2*new_seq_merit);

        if (exp((E_seq-E_new_seq)/T) >= r ){
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
