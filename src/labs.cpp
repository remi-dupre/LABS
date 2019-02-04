#include "labs.hpp"


bool is_valid_sequence(const Sequence& seq)
{
    for (const char x: seq)
        if (x != 1 && x != -1)
            return false;

    return true;
}

long long unsigned hash(const Sequence& seq)
{
    unsigned result = 0;

    for (int x : seq)
        result = (3 * result + (x + 1) / 2) % 1000000009;

    return result;
}

double autocorrelation(const Sequence& seq, int k)
{
    assert(is_valid_sequence(seq));
    assert(k > 0 && k < (int) seq.size());

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
    assert(is_valid_sequence(seq));

    running_local_mode = true;
    local_current_seq = seq;

    double energy = 0;
    ck_cached_local = std::vector<double>(seq_size, 0);

    // Compute initial autocorrelations
    for (int k = 1 ; k < seq_size ; k++) {
        ck_cached_local[k] = autocorrelation(seq, k);
        energy += std::pow(ck_cached_local[k], 2);
    }

    return (seq_size * seq_size) / (2 * energy);
}

void LabsInstance::leave_local_mode()
{
    assert(running_local_mode);

    running_local_mode = false;
}

double LabsInstance::oracle_merit() const
{
    assert(running_local_mode);

    double energy = 0;

    for (const double Ck: ck_cached_local)
        energy += std::pow(Ck, 2);

    return std::pow(seq_size, 2) / (2 * energy);
}

double LabsInstance::oracle_merit(int i)
{
    assert(running_local_mode);

    swap_spin(i, false);
    const double merit = oracle_merit();
    swap_spin(i, false);
    return merit;
}

double LabsInstance::swap_spin(int i, bool history_checkpoint)
{
    assert(running_local_mode);

    for (int j = 0 ; j < seq_size; j++) {
        if (i != j) {
            const int k = std::abs(i - j);
            ck_cached_local[k] -= \
                2 * local_current_seq[i] * local_current_seq[j];
        }
    }

    count_atomic_swaps++;
    local_current_seq[i] *= -1;

    if (history_checkpoint)
        update_history(local_current_seq);

    return oracle_merit();
}

Sequence LabsInstance::local_checkpoint()
{
    update_history(local_current_seq);
    return local_current_seq;
}

long long int LabsInstance::get_nb_atomic_swaps() const
{
    return count_atomic_swaps;
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

