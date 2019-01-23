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
    running_local_mode(false),
    count_atomic_swaps(0)
{
    time_start = std::chrono::system_clock::now();
}

double LabsInstance::eval(const Sequence& seq)
{
    assert(!running_local_mode);

    update_history(seq);
    return merit(seq);
}

double LabsInstance::init_local_mode(const Sequence& seq)
{
    running_local_mode = true;

    double energy = 0;
    Ck_oracle = std::vector<std::vector<double>>
        (seq_size, std::vector<double>(seq_size, 0));

    // Compute initial autocorrelations
    for (int k = 0 ; k < seq_size ; k++) {
        const double autocorr = autocorrelation(seq, k);

        for (int i = 0 ; i < seq_size ; i++)
            Ck_oracle[i][k] = autocorr;

        energy += Ck_oracle[0][k] * Ck_oracle[0][k];
    }

    // Compte initial oracles
    for (int k = 0 ; k < seq_size ; k++) {
        for (int i = 0 ; i < seq_size - k ; i++) {
            const double offset = -2 * seq[i] * seq[i+k];
            Ck_oracle[i][k] += offset;
            Ck_oracle[i+k][k] += offset;
        }
    }

    return (seq_size * seq_size) / (2 * energy);
}

void LabsInstance::leave_local_mode()
{
    assert(running_local_mode);
    running_local_mode = false;
}

double LabsInstance::oracle_merit(int i)
{
    assert(running_local_mode);

    double energy = 0;

    for (int k = 0 ; k < seq_size ; k++)
        energy += Ck_oracle[i][k];

    return (seq_size * seq_size) / (2 * energy);
}

Sequence LabsInstance::swap_spin(int i)
{
    assert(running_local_mode);

    Sequence last = requests.back();

    for (int k = 0 ; k < seq_size - i ; k++) {
        Ck_oracle[i][k] -= 2 * last[i] * last[i+k];
        Ck_oracle[i+k][k] -= 2 * last[i] * last[i+k];
    }

    last[i] *= -1;
    update_history(last);
    count_atomic_swaps++;
    return last;
}

long long int LabsInstance::get_nb_requests() const
{
    return requests.size();
}

std::vector<Sequence> LabsInstance::get_requests() const
{
    return requests;
}

std::vector<std::chrono::duration<double>> LabsInstance::get_requests_timers() const
{
    return requests_timers;
}

void LabsInstance::update_history(const Sequence& seq)
{
    assert(is_valid_sequence(seq));
    assert((int) seq.size() == seq_size);

    auto time_eval = std::chrono::system_clock::now();
    requests.push_back(seq);
    requests_timers.push_back(time_eval - time_start);
}

