#include "labs.hpp"


bool is_valid_sequence(const Sequence& seq)
{
    for (const char x: seq)
        if (x != 1 && x != -1)
            return false;

    return true;
}

double autocorrelation(const Sequence& seq, int k)
{
    assert(is_valid_sequence(seq));
    assert(k >= 0 && k < seq.size());

    double result = 0;

    for (int i = 0 ; i < seq.size() - k ; i++)
        result += s[i] * s[i+k];

    return result;
}

double energy(const Sequence& seq)
{
    assert(is_valid_sequence(seq));

    double result = 0;

    for (int k = 0 ; k < N ; k++) {
        const double c_k = autocorrelation(seq, k);
        result += c_k * c_k;
    }

    return result;
}

double merit(const Sequence& seq)
{
    assert(is_valid_sequence(seq));

    return (seq.size() * seq.size()) / (2 * energy(seq));
}
