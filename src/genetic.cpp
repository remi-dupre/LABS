#include "genetic.hpp"


Genetic::Genetic(int seq_size, int seed, int nb_iter, int nb_parents, int nb_childs) :
    Optimizer(seq_size, seed)
{
    name = "genetic";
    params = {
        {"iterations", (int) nb_iter},
        {"nb_parents" , (int) nb_parents},
        {"nb_childs" , (int) nb_childs}
    };
}


Sequence Genetic::run(LabsInstance& instance)
{
    std::vector<Sequence> population(params["nb_parents"],random_sequence());
    for(int i = 0; i < params["nb_parents"]; i++) population[i] = random_sequence();

    for (int step = 0 ; step < params["iterations"] ; step++) {
      std::vector<std::pair<Sequence,double>> childs;
      for(int l = 0; l < params["nb_childs"]; l++) {
        int i =  rand() % (int)params["nb_parents"];
        int j =  rand() % (int)params["nb_parents"];
        Sequence seq = random_sequence();
        for(int k = 0; k < seq_size; k++) {
          if (rand()%2 == 0){
            seq[k] = population[i][k];
          }
          else {
            seq[k] = population[j][k];
          }
          childs.push_back(std::make_pair(seq, instance.eval(seq)));
        }
      }

      std::sort (childs.begin(), childs.end(), [&](const auto& a, const auto& b)
        {
            return a.second > b.second;
        });
      for(int i = 0; i < params["nb_parents"]; i++) population[i] = childs[i].first;
      if (step % 10 == 0) std::cout << "eval " << step << " " << instance.eval(population[0]) << std::endl;
    }
    return population[0];
}
