#pragma once

#include "json.hpp"

#include "optimizer.hpp"
#include "corr_max.hpp"


/**
 * Display a serialized report of a sequence of tests.
 */
typedef std::pair<
    std::map<std::string, std::string>,  // general description of the test
    std::vector<Optimizer*>              // list of optimizers to run
> Test;

void json_benchmark(const Optimizer& opt, std::ostream& stream, bool light, const std::string& line_prefix);
void run_output_tests(std::ostream& stream, const std::vector<Test>& tests);
