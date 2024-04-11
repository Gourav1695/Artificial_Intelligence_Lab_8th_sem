is_prime(N) :- N > 1, is_prime_helper(N, 2).

is_prime_helper(N, I) :- I > sqrt(N), !.

is_prime_helper(N, I) :- N mod I =\= 0, I_next is I + 1, is_prime_helper(N, I_next).

goldbach(N, L) :- goldbach_helper(N, 2, 0, L).

goldbach_helper(1, _, 0, []) :- !.

goldbach_helper(N, I, C, [I | L]) :- C < 2, C1 is C + 1, is_prime(I), I1 is N - I, is_prime(I1), goldbach_helper(N, I1, C1, L), !.

goldbach_helper(N, I, C, L) :- I >= N, !.

goldbach_helper(N, I, C, L) :- I_next is I + 1, goldbach_helper(N, I_next, C, L).