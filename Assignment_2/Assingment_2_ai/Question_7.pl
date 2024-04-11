combinations(0,_,[]).
combinations(N,[_|R], Res):- 
    N>0, 
    combinations(N,R, Res).
combinations( N,[H|R], Res):- 
    N>0,
    N2 is N-1, 
    combinations(N2, R,Res1), 
    append([H],Res1, Res).

    