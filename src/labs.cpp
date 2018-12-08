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
    assert(k >= 0 && k < (int) seq.size());

    double result = 0;

    for (size_t i = 0 ; i < seq.size() - k ; i++)
        result += seq[i] * seq[i+k];

    return result;
}

double energy(const Sequence& seq)
{
    assert(is_valid_sequence(seq));

    double result = 0;

    for (size_t k = 1 ; k < seq.size() ; k++) {
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


LabsInstance::LabsInstance(int seq_size) :
    seq_size(seq_size),
    request_counter(0)
{}

double LabsInstance::eval(const Sequence& seq)
{
    assert(is_valid_sequence(seq));
    assert((int) seq.size() == seq_size);

    request_counter++;
    return merit(seq);
}

long long int LabsInstance::get_nb_requests() const
{
    return request_counter;
}
