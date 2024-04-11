is_sub_list([],_).
is_sub_list([X|R1], [X|R2]):- 
 check_sublist(R1,R2).
is_sub_list([X|R1],[_|R2]):- 
  is_sub_list([X|R1],R2). 

check_sublist([],_). 
check_sublist([X|R1],[X|R2]):- 
  check_sublist(R1,R2).