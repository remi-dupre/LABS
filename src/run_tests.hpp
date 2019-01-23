#pragma once

#include "json.hpp"

#include "optimizers/optimizer.hpp"
#include "optimizers/corr_max.hpp"
#include "optimizers/genetic.hpp"
#include "optimizers/local_random.hpp"
#include "optimizers/simulated_annealing.hpp"


/**
 * Display a serialized report of a sequence of tests.
 */
typedef std::pair<
    std::map<std::string, std::string>,  // general description of the test
    std::vector<Optimizer*>              // list of optimizers to run
> Test;

void json_benchmark(const Optimizer& opt, std::ostream& stream, bool light, const std::string& line_prefix);
void run_output_tests(std::ostream& stream, const std::vector<Test>& tests);

