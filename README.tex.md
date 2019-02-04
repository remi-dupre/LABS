Low Autocorrelation Binary Sequence
===================================

By Garance Gourdel and Rémi Dupré.

This project is part of the MPRI course 2-24-2, *Solving Optimization Problems
with Search Heuristics*.

Consider a sequence $S = (s_1, ..., s_N)$ with $s_i = \pm 1$. The autocorrelation of S are defined as follow:
  $$C_k(S) = \sum\limits_{i=1}^{N-k} s_i s_{i+k}$$
  
for $k = 0, 1, ..., N-1$ and the *energy* of S is defined as the sum of the squares of all offpeak correlations
  $$E(S) = \sum\limits_{k=1}^{N-1} C_k^2(S)$$.

The *low-autocorrelation binary sequence* (LABS) problem is to find a sequence S of given length $N$ that minimizes $E(S)$ or, equivalently, maximizes the *merit factor*
  $$F(S) = \frac{N^2}{2 E(S)}$$.

This minimization problem has applications has applications in communications engineering (as it is used to find modulation pulses in radar and sonar ranging) and physics (where $E(S)/N$ can be interpreted as the energy of $N$ interacting Ising spins).

Compilation
===================================
The project is written in C++ 14 for the implementation of the solutions and Python 3 to plot the different graphs. The plot module also has dependencies on `glob` `json` and `matplotlib`.

To compile the project you will also need `make` and the different uses are :
 - `make release` will create a binary `simulation` that you can execute by the command `./simulation` that will output a json in the folder `data`.
 - then using a `make plot` will lauch `plot/main.py` which take the json in `data` and output graphs in the folder `figure`.
 

