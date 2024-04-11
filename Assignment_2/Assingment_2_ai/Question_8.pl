/* bubble sort */
getHead([H|_], H). 
getRest([_|R], R).
bubble_sort(List, Res):- 
  bub_sort(List,List, Res).

bub_sort([],R,R).
bub_sort([_|R],List,Result):-
    bubble(List,Res1), 
    bub_sort(R,Res1,Result).

bubble([H],[H]). 
bubble([H|R],Result):- 
    getHead(R,H2), 
    H<H2, 
    bubble(R,Res1), 
    append([H],Res1, Result).
bubble([H|R], Result):- 
    getHead(R,H2),
    H>=H2, 
    getRest(R,Rest),
append([H], Rest, R1), 
bubble(R1, Res1), 
append([H2],Res1, Result).