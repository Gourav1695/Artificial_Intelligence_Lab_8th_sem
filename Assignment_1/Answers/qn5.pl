% 5. To find the kth element of a list. 
 
element_at([X|_], 1, X). 
element_at([_|T], K, X) :- 
    K > 1, 
    K1 is K - 1, 
    element_at(T, K1, X). 