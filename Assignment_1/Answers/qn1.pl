% Base case: When the list has only one element
last_element([X], X).

% Recursive case: When the list has more than one element
last_element([Y|T], X) :-
    last_element(T, X).
