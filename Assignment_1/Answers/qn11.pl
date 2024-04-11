fib(0, [0]). 
fib(1, [0, 1]). 
fib(2, [0, 1, 1]). 
 
fib(N, L) :- 
    N > 2, 
    N1 is N - 1, 
    N2 is N - 2, 
    fib(N1, F1), 
    last(F1, L1), 
    fib(N2, F2), 
    last(F2, L2), 
    L_new is L1 + L2, 
    append(F1, [L_new], L).