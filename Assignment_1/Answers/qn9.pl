is_prime(N) :- N > 1, is_prime_helper(N, 2). 
 
is_prime_helper(N, I) :- I > sqrt(N), !. 
 
is_prime_helper(N, I) :- N mod I =\= 0, I_next is I + 1, is_prime_helper(N, 
I_next). 
 
prime_factors(N, L) :- prime_factors_helper(N, 2, L). 
 
prime_factors_helper(1, _, []) :- !. 
 
prime_factors_helper(N, I, [I|L]) :- is_prime(I),  N mod I =:= 0, N1 is N // 
I, prime_factors_helper(N1, I, L). 
 
prime_factors_helper(N, I, L) :- I_next is I + 1, prime_factors_helper(N, 
I_next, L).