#include "harmonic_search.hpp"


HarmonicSearch::HarmonicSearch(int seq_size, int seed, int nb_iterations) :
    Optimizer(seq_size, seed)
{
    name = "harmonic_search";
    params = {
        {"nb_iterations", nb_iterations}
    };
}

Sequence HarmonicSearch::run(LabsInstance& instance)
{
    Sequence seq = random_sequence();
    double current_merit = instance.init_local_mode(seq);

    for (int it = 0 ; it < params["nb_iterations"] ; it++) {
        // Pick a random period and offset
        std::uniform_int_distribution<int> period_dist(1, seq_size);
        const int period = period_dist(random_engine);

        std::uniform_int_distribution<int> offset_dist(0, period-1);
        const int offset = offset_dist(random_engine);

        // Try to swaps bits using this period / offset
        const double new_merit = swap_period(instance, period, offset);

        if (new_merit > current_merit) {
            current_merit = new_merit;
            seq = instance.local_checkpoint();
        }
        else {
            swap_period(instance, period, offset);
        }
    }

    return seq;
}

double HarmonicSearch::swap_period(LabsInstance& instance, int period, int offset)
{
    assert(0 < period && period <= seq_size);
    assert(0 <= offset && offset < period);

    double merit = -1;

    for (int i = offset ; i < seq_size ; i += period)
        merit = instance.swap_spin(i, false);

    return merit;
}

