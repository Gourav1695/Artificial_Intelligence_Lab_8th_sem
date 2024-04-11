prime_factors(N, L) :-
    prime_factors(N, [], L).

prime_factors(1, L, L).
prime_factors(N, Acc, L) :-
    N > 1,
    between(2, N, D),
    0 is mod(N, D), !,
    prime_factors(N // D, [D | Acc], L).
prime_factors(N, Acc, L) :-
    N > 1,
    M is N - 1,
    prime_factors(M, Acc, L).
