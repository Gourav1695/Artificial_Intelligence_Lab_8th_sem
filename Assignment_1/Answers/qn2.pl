% 2. Concatenating two lists 
concatenate_lists([], List, List). 
concatenate_lists([Head|Tail1], List2, [Head|Result]) :- 
    concatenate_lists(Tail1, List2, Result).