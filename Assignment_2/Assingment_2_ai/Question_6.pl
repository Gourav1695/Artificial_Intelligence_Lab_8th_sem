/* slice(List,Start,End,Res) */ 
slice([H|_],1,1,[H]). 
slice([H|R],1,End,Res):- 
    End2 is End-1, 
    slice(R,1,End2,Res2), 
    append([H],Res2,Res).
slice([_|R], Start,End,Res):- 
    Start >1,
    Start2 is Start-1,
    End2 is End-1,
    slice(R,Start2,End2,Res).