transpose([],[],[]). 
transpose([H1|R1],[H2|R2],Res) :- 
    transpose(R1,R2,Res1), 
    append([(H1,H2)],Res1,Res).