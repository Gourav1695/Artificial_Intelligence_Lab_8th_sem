/* Implement merge_sort(Lis, Res) */ 
split(L,0,[],L). 
split([H|R],N, L1,L2):-
 N2 is N-1, 
 split(R,N2,Tl1,L2), 
 append([H], Tl1,L1).

merge_sort([H],[H]). 
merge_sort(List, Res):- 
  length(List,Len), 
  Len>1, 
  Len2 is integer(Len/2), 
  split(List,Len2, L1, L2), 
  merge_sort(L1,Res1), 
  merge_sort(L2,Res2), 
  merge(Res1,Res2,Res).

merge([],L,L).
merge(L,[],L). 
merge([H1| R1], [H2| R2], Res):-
    H1 =< H2, 
    merge(R1, [H2|R2], Res1),
    append([H1],Res1, Res). 
merge([H1|R1], [H2|R2], Res):-
    H2 <H1,
    merge([H1|R1], R2, Res1),
    append([H2], Res1, Res).