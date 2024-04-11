append_lists([], L, L). 
append_lists([H|T1], L2, [H|Result]) :- 
    append_lists(T1, L2, Result). 
append_K_times(_,0,[]). 
append_K_times(H,N,[H|R]):- 
    N>0,
    N1 is N-1,
    append_K_times(H,N1,R). 
duplicate([],_,[]).
duplicate([H|R],N,X):- 
    duplicate(R,N,Remains),
    append_K_times(H,N,HeadNtimes),
    append_lists(HeadNtimes,Remains,X).