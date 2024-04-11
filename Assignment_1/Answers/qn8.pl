% 8. To determine whether a given integer number is prime or not. 
is_prime(2). 
is_prime(3). 
is_prime(P) :- 
    P > 3, 
    P mod 2 =\= 0, 
    \+ has_factor(P, 3). 
 
has_factor(N, Factor) :- 
    Factor * Factor =< N, 
    (N mod Factor =:= 0 ; NextFactor is Factor + 2, has_factor(N, 
NextFactor)). 