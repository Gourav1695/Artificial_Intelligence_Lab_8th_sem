split(L, 0, [], L).
split([X|Xs], N, [X|L1], L2) :-
    N > 0,
    N1 is N - 1,
    split(Xs, N1, L1, L2).
