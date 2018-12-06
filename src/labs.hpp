/**
 * Basic behaviour of Low Autocorrelation Binary Sequence problem which consist
 * of minimizing the merit factor over fixed size binary sequences.
 */
#pragma once

#include <cassert>
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
