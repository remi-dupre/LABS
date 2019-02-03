#pragma once

#include <cassert>

#include "json.hpp"

#include "optimizers/corr_max.hpp"
#include "optimizers/genetic.hpp"
#include "optimizers/harmonic_search.hpp"
#include "optimizers/local_search.hpp"
#include "optimizers/local_branching.hpp"
#include "optimizers/optimizer.hpp"
#include "optimizers/simulated_annealing.hpp"


/**
 * Display a serialized report of a sequence of tests.
 */
typedef std::pair<
    std::map<std::string, std::string>,  // general description of the test
    std::vector<Optimizer*>              // list of optimizers to run
> Test;

/* Run tests for all input optimizers and output result in the stream using
 * json serializer.
 */
void run_output_tests(std::ostream& stream, const std::vector<Test>& tests,
    int nb_tests = 1);

