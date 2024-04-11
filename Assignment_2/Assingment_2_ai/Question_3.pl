union([],L,L).
union([X|R],L,Res):-
  member(X,L), 
  union(R,L,Res). 
union([X|R], L,Res):- 
  \+ member(X,L),
   union(R,L,R1), 
   append([X],R1, Res). 

intersection([],_,[]). 
intersection([X|R],L, Res):- 
   member(X,L),
   intersection(R,L,Res1), 
   append([X],Res1,Res).
intersection([X|R],L,Res):- 
   \+ member(X,L),
    intersection(R,L,Res). 
subtract([],_,[]). 
subtract([H|R],I,Res):- 
   member(H,I), 
   subtract(R,I,Res).

subtract([H|R],I,Res):-
 \+ member(H,I),
  subtract(R,I,Res1), 
  append([H],Res1,Res). 
  
sym_dif(L1,L2,Res):- 
 union(L1,L2,U), 
 intersection(L1,L2,I), 
 subtract(U,I,Res).