#include "optimizer.hpp"


Optimizer::Optimizer(int seq_size, int seed) :
    seq_size(seq_size),
    random_engine(seed)
{}

Sequence Optimizer::run()
{
    LabsInstance instance(seq_size);
    return run(instance);
}

Sequence Optimizer::random_sequence()
{
    std::uniform_int_distribution<char> dist(0, 1);
    Sequence seq(seq_size);

    for (char& x: seq)
        x = dist(random_engine) * 2 - 1;

    return seq;
}

Sequence ExampleOpt::run(LabsInstance& instance)
{
    Sequence best_seq = random_sequence();
    double best_score = instance.eval(best_seq);

    for (int i = 0 ; i < 1000 ; i++) {
        Sequence new_seq = random_sequence();
        double new_score = instance.eval(new_seq);

        if (new_score > best_score) {
            best_seq = new_seq;
            best_score = new_score;
        }
    }

    return best_seq;
}
