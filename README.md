Low Autocorrelation Binary Sequence
===================================

By Garance Gourdel and Rémi Dupré.

This project is part of the MPRI course 2-24-2, *Solving Optimization Problems
with Search Heuristics*.

Consider a sequence <img src="/tex/cbab8293a67c5a76af9ca58e8fa92641.svg?invert_in_darkmode&sanitize=true" align=middle width=109.29435659999999pt height=24.65753399999998pt/> with <img src="/tex/2753ae85cbbcf191452b722ffcd60990.svg?invert_in_darkmode&sanitize=true" align=middle width=56.100549449999995pt height=21.18721440000001pt/>. The autocorrelation of S are defined as follow:
  <p align="center"><img src="/tex/a4abdabe54550232ce5ad245136fc729.svg?invert_in_darkmode&sanitize=true" align=middle width=140.38511685pt height=47.93392394999999pt/></p>
  
for <img src="/tex/f6ef1610f63fa83bea49414724997f77.svg?invert_in_darkmode&sanitize=true" align=middle width=126.35810219999998pt height=22.831056599999986pt/> and the energy of S is defined as the sum of the squares of all offpeak correlations
  <p align="center"><img src="/tex/57652d0040949bbf9d5c313c1ab52108.svg?invert_in_darkmode&sanitize=true" align=middle width=134.13687045pt height=48.18280005pt/></p>.

The *low-autocorrelation binary sequence* (LABS) problem is to find a sequence S of given length <img src="/tex/f9c4988898e7f532b9f826a75014ed3c.svg?invert_in_darkmode&sanitize=true" align=middle width=14.99998994999999pt height=22.465723500000017pt/> that minimizes <img src="/tex/2e53563baea25d6c9cc9187eea827cb7.svg?invert_in_darkmode&sanitize=true" align=middle width=36.89499329999999pt height=24.65753399999998pt/> or, equivalently, maximizes the <img src="/tex/bcc6a7b2e1e3ec43a7b568973458656f.svg?invert_in_darkmode&sanitize=true" align=middle width=88.95699119999999pt height=22.831056599999986pt/>
  <p align="center"><img src="/tex/ed215203a579d32f7e4edbd10d2426d8.svg?invert_in_darkmode&sanitize=true" align=middle width=105.67116945pt height=39.887022449999996pt/></p>.
