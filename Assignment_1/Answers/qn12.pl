parent(john,ann). 
parent(jim,john). 
parent(jim,keith). 
parent(mary,ann). 
parent(mary,sylvia). 
parent(brian,sylvia). 
male(keith). 
male(jim). 
female(sylvia). 
female(ann). 
male(brian). 
 
uncle(X, Y) :- male(X), parent(Z, Y), parent(A, Z), parent(A, X). 
 
half_sister(X, Y) :- female(X), parent(Z, X), parent(Z, Y), parent(A, X), A \= 
Z, parent(B, Y), B \= Z, A \= B.