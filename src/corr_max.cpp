#include "corr_max.hpp"


Sequence CorrMax::run(LabsInstance& instance)
{
    Sequence seq = random_sequence();
    double seq_merit = instance.eval(seq);

    for (int step = 0 ; step < 10000 ; step++) {
        // Try to reduce as much as possible a random correlation coefficient
        std::uniform_int_distribution<int> dist_k(0, seq_size - 1);
        const int k = dist_k(random_engine);
        const double correlation_k = autocorrelation(seq, k);

        // Select an index that minimizes the new C_k
        std::vector<double> contrib(seq_size, 0);

        for (int i = 0 ; i < seq_size - k ; i++) {
            if (seq[i] * seq[i+k] < 0) {
                contrib[i] += 2;
                contrib[i+k] += 2;
            }
            else {
                contrib[i] -= 2;
                contrib[i+k] -= 2;
            }
        }

        for (int i = 0 ; i < seq_size ; i++)
            contrib[i] = abs(correlation_k + contrib[i]);

        // Select a random candidate among thoose who minimize C_k
        const double best_new_ck = *min_element(contrib.begin(), contrib.end());
        std::vector<int> candidates;

        for (int i = 0 ; i < seq_size ; i++)
            if (contrib[i] - best_new_ck < 1)
                candidates.push_back(i);

        std::uniform_int_distribution<int> dist_i(0, candidates.size() - 1);
        const int i = dist_i(random_engine);

        // Swap selected bit if merit increased
        seq[i] *= -1;
        const double new_merit = instance.eval(seq);

        if (seq_merit > new_merit)
            seq[i] *= -1;
        else
            seq_merit = new_merit;
    }

    return seq;
}
