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

void Optimizer::json_benchmark(std::ostream& stream)
{
    // Prompt some informations
    std::cout << " - Running `" << name << "`\n    ";
    serialize_json(std::cout, "N", seq_size);
    std::cout << "\n    ";
    serialize_json(std::cout, "params", params);
    std::cout << std::endl;

    // Run an instance of labs
    const auto start = std::chrono::system_clock::now();
    LabsInstance instance(seq_size);
    const auto seq = run(instance);
    const auto end = std::chrono::system_clock::now();

    const std::chrono::duration<double> duration = end - start;

    // Preprocess steps informations
    std::vector<std::map<std::string, double>> steps(instance.get_nb_requests());

    auto requests = instance.get_requests();
    for (size_t i = 0 ; i < requests.size() ; i++)
        steps[i]["merit"] = merit(requests[i]);

    auto requests_timers = instance.get_requests_timers();
    for (size_t i = 0 ; i < requests_timers.size() ; i++)
        steps[i]["time"] = requests_timers[i].count();

    // Output result;
    stream << "{\n\t";
    serialize_json(stream, "name", name);
    stream << ",\n\t";
    serialize_json(stream, "params", params);
    stream << ",\n\t";
    serialize_json(stream, "dim", seq_size);
    stream << ",\n\t";
    serialize_json(stream, "running_time", duration.count());
    stream << ",\n\t";
    serialize_json(stream, "output", seq);
    stream << ",\n\t";
    serialize_json(stream, "merit", merit(seq));
    stream << ",\n\t";
    serialize_json(stream, "steps", steps);
    stream << "\n}";
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
