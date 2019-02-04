#include "optimizer.hpp"


Optimizer::Optimizer(int seq_size, int seed) :
    seq_size(seq_size),
    random_engine(seed)
{}

Sequence Optimizer::run()
{
    srand (random_engine());
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

void Optimizer::json_benchmark(std::ostream& stream, bool light,
    int nb_tests, const std::string& line_prefix)
{
    assert(nb_tests > 0);

    // Prompt some informations
    std::cout << " - Running `" << name << "`\n    ";
    serialize_json(std::cout, "N", seq_size);
    std::cout << "\n    ";
    serialize_json(std::cout, "params", params);
    std::cout << "\n    ";
    serialize_json(std::cout, "nb_tests", nb_tests);
    std::cout << "\n    ";

    // Run instances of labs
    Sequence best_seq;
    LabsInstance best_instance(seq_size);
    int best_merit = -1, sum_merit = 0;
    double best_merit_time = 0, sum_time = 0;

    for (int k = 0 ; k < nb_tests ; k++) {
        // Run one instance
        const auto start = std::chrono::system_clock::now();
        LabsInstance instance(seq_size);

        const auto seq = run(instance);

        const auto end = std::chrono::system_clock::now();
        const std::chrono::duration<double> duration = end - start;

        // Update stats
        sum_merit += merit(seq);
        sum_time += duration.count();

        if (merit(seq) > best_merit) {
            best_seq = seq;
            best_merit = merit(seq);
            best_merit_time = duration.count();
            best_instance = instance;
        }
    }

    serialize_json(std::cout, "result", merit(best_seq));
    std::cout << "\n    ";
    serialize_json(std::cout, "time", best_merit_time);
    std::cout << std::endl;

    // Preprocess steps informations
    std::vector<std::map<std::string, double>> steps(
        best_instance.get_nb_requests());

    auto requests = best_instance.get_requests();
    for (size_t i = 0 ; i < requests.size() ; i++)
        steps[i]["merit"] = merit(requests[i]);

    auto requests_timers = best_instance.get_requests_timers();
    for (size_t i = 0 ; i < requests_timers.size() ; i++)
        steps[i]["time"] = requests_timers[i].count();

    // Output result;
    stream << "{\n" << line_prefix << "\t";
    serialize_json(stream, "name", name);
    stream << ",\n" << line_prefix << "\t";
    serialize_json(stream, "params", params);
    stream << ",\n" << line_prefix << "\t";
    serialize_json(stream, "dim", seq_size);
    stream << ",\n" << line_prefix << "\t";
    serialize_json(stream, "running_time", best_merit_time);
    stream << ",\n" << line_prefix << "\t";
    serialize_json(stream, "nb_requests",
        (int) best_instance.get_nb_requests());
    stream << ",\n" << line_prefix << "\t";
    serialize_json(stream, "nb_atomic_swaps",
        (int) best_instance.get_nb_atomic_swaps());
    stream << ",\n" << line_prefix << "\t";
    serialize_json(stream, "output", best_seq);
    stream << ",\n" << line_prefix << "\t";
    serialize_json(stream, "merit", merit(best_seq));
    stream << ",\n" << line_prefix << "\t";
    serialize_json(stream, "mean_merit", sum_merit / (double) nb_tests);
    stream << ",\n" << line_prefix << "\t";
    serialize_json(stream, "mean_time", sum_time / (double) nb_tests);

    if (!light) {
        stream << ",\n" << line_prefix << "\t";
        serialize_json(stream, "steps", steps, line_prefix);
    }

    stream << "\n" << line_prefix << "}";
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
