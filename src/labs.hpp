/**
 * Basic behaviour of Low Autocorrelation Binary Sequence problem which consist
 * of minimizing the merit factor over fixed size binary sequences.
 */
#pragma once

#include <cassert>
#include <chrono>
#include <vector>


typedef std::vector<char> Sequence;


/* Verify that a sequence is consistant, it should only contain values 1 or -1.
 */
bool is_valid_sequence(const Sequence& seq);

/* Compute the autocorrelation coefficient of order k C_k(seq) of a sequence.
 */
double autocorrelation(const Sequence& seq, int k);

/* Compute the energy E(seq) of a sequence.
 */
double energy(const Sequence& seq);

/* Compute the merit factor F(seq) of a sequence.
 */
double merit(const Sequence& seq);


/* Helper to count number of requests while running an optimization algorithm.
 */
class LabsInstance {
public:
    /* Init the instance for a given size of sequence.
     */
    LabsInstance(int seq_size);

    /* Get the merit factor of a sequence
     */
    double eval(const Sequence& seq);

    /* Get the number of requests so far
     */
    long long int get_nb_requests() const;

    /* Get the list of requested sequences so far
     */
    std::vector<Sequence> get_requests() const;

    /* Get the timestamps at which the requests started
     */
    std::vector<std::chrono::duration<double>> get_requests_timers() const;

private:
    int seq_size;
    std::chrono::time_point<std::chrono::system_clock> time_start;
    std::vector<Sequence> requests;
    std::vector<std::chrono::duration<double>> requests_timers;
};
