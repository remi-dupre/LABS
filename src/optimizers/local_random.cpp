#include "local_random.hpp"


LocalRandom::LocalRandom(int seq_size, int seed, int nb_iter) :
    Optimizer(seq_size, seed)
{
    name = "local_random";
    params = {
        {"iterations", (double) nb_iter}
    };
}

Sequence LocalRandom::run(LabsInstance& instance)
{

}

