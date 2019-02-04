/**
 * Basic behaviour of Low Autocorrelation Binary Sequence problem which consist
 * of minimizing the merit factor over fixed size binary sequences.
 */
#pragma once

#include <cassert>
#include <chrono>
#include <cmath>
#include <vector>


typedef std::vector<char> Sequence;


/* Verify that a sequence is consistant, it should only contain values 1 or -1.
 */
bool is_valid_sequence(const Sequence& seq);

/* Return an hash of given sequence
 */
long long unsigned hash(const Sequence& seq);

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

    /* Get the merit factor of a sequence (do not use in local mode)
     */
    double eval(const Sequence& seq);

    /* Activate local mode: precompute an oracle on C_k's of adjacent
     * sequences, then only swapping one bit at once is allowed, this initial
     * operation takes O(seq_size²) steps to run. It also returns the merit of
     * the input sequence.
     *
     * It can also be used to "jump" to an arbitrary sequence during a run
     * using local mode.
     */
    double init_local_mode(const Sequence& seq);

    /* Exit from local mode
     */
    void leave_local_mode();

    /* In local mode, get the energy of current sequence */
    double oracle_merit() const;

    /* In local mode, get the energy resulting of spining bit i of the last
     * submited sequence.
     */
    double oracle_merit(int i);

    /* In local mode, spin one bit of the last submitted sequence, output the
     * merit of resulting sequence, which is now the last submitted sequence.
     */
    double swap_spin(int i, bool history_checkpoint = false);

    /* Add current state of the local mode in the history and return current
     * sequence.
     */
    Sequence local_checkpoint();

    long long int get_nb_atomic_swaps() const;

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
    /* Update the history with given sequence
     */
    void update_history(const Sequence& seq);

    // constant size for the instance of the problem
    int seq_size;

    // Time of creation of the instance
    std::chrono::time_point<std::chrono::system_clock> time_start;

    // History of evaluated sequences
    std::vector<Sequence> requests;

    // History of evaluation timings
    std::vector<std::chrono::duration<double>> requests_timers;

    // If set to true, it means this is running in local mode
    bool running_local_mode;

    // Count the number of atomic swap run in local mode
    long long int count_atomic_swaps;

    // Cache on the values of the C_k while running in local mode
    std::vector<double> ck_cached_local;

    // Cache on the current sequence while running in local mode
    Sequence local_current_seq;
};

