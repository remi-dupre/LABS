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

void Optimizer::json_benchmark()
{
    // Run an instance of labs
    const auto start = std::chrono::system_clock::now();
    LabsInstance instance(seq_size);
    const auto seq = run(instance);
    const auto end = std::chrono::system_clock::now();

    const std::chrono::duration<double> duration = end - start;

    // Output result
    std::cout << "{" << std::endl;

    std::cout << "\t" << json_value("name", name) << ",\n";
    std::cout << "\t" << json_value("params", params) << ",\n";
    std::cout << "\t" << json_value("dim", seq_size) << ",\n";
    std::cout << "\t" << json_value("running_time", duration.count()) << ",\n";
    std::cout << "\t" << json_value("output", seq) << ",\n";
    std::cout << "\t" << json_value("merit", merit(seq)) << "\n";
    // std::cout << "\t" << json_value("steps", instance.get_requests()) << ",\n";

    std::cout << "}";
}

ExampleOpt::ExampleOpt(int seq_size, int seed, int nb_iter) :
    Optimizer(seq_size, seed)
{
    name = "full_random";
    params["iterations"] = (double) nb_iter;
}

Sequence ExampleOpt::run(LabsInstance& instance)
{
    Sequence best_seq = random_sequence();
    double best_score = instance.eval(best_seq);

    for (int i = 0 ; i < params["iterations"] ; i++) {
        Sequence new_seq = random_sequence();
        double new_score = instance.eval(new_seq);

        if (new_score > best_score) {
            best_seq = new_seq;
            best_score = new_score;
        }
    }

    return best_seq;
}
