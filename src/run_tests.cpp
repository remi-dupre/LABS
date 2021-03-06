#include "run_tests.hpp"


void run_output_tests(std::ostream& stream, const std::vector<Test>& tests,
    int nb_tests)
{
    assert(nb_tests > 0);

    stream << "[\n";
    bool first_test = true;

    for (const auto& test : tests) {
        if (first_test) {
            first_test = false;
            stream << "\n\t";
        }
        else {
            stream << ", ";
        }

        const auto& description = test.first;
        const auto& optimizers = test.second;

        stream << "{";

        // display descriptions
        for (const auto& key_val : description) {
            stream << "\n\t\t";
            serialize_json(stream, key_val.first, key_val.second);
            stream << ",";
        }

        stream << "\n\t\t";

        // run test
        stream << "\"dataset\": [";

        for (size_t i = 0 ; i < optimizers.size() ; i++) {
            const bool with_history = description.count("with_history")
                && description.at("with_history") == "yes";

            if (optimizers[i]->name == "full_random")
                static_cast<ExampleOpt*>(optimizers[i])->json_benchmark(stream,
                    !with_history, nb_tests, "\t\t");

            if (optimizers[i]->name == "maximize_correlation")
                static_cast<CorrMax*>(optimizers[i])->json_benchmark(stream,
                        !with_history, nb_tests, "\t\t");

            if (optimizers[i]->name == "genetic")
                static_cast<Genetic*>(optimizers[i])->json_benchmark(stream,
                        !with_history, nb_tests, "\t\t");

            if (optimizers[i]->name == "threshold_localsearch")
                static_cast<Threshold_Localsearch*>(optimizers[i])->json_benchmark(stream,
                        !with_history, nb_tests, "\t\t");

            if (optimizers[i]->name == "simulated_annealing")
                static_cast<Simulated_Annealing*>(optimizers[i])->json_benchmark(stream,
                        !with_history, nb_tests, "\t\t");

            if (optimizers[i]->name == "local_search")
                static_cast<LocalSearch*>(optimizers[i])->json_benchmark(
                    stream, !with_history, nb_tests, "\t\t");

            if (optimizers[i]->name == "local_branching")
                static_cast<LocalBranching*>(optimizers[i])->json_benchmark(
                    stream, !with_history, nb_tests, "\t\t");

            if (optimizers[i]->name == "harmonic_search")
                static_cast<HarmonicSearch*>(optimizers[i])->json_benchmark(
                    stream, !with_history, nb_tests, "\t\t");

            if (i + 1 < optimizers.size())
                stream << ", ";
        }

        stream << "\n\t\t]\n\t}";
    }

    stream << "\n]\n";
}
