/*
pack([a, a, a, a, b, c, c, a, a, d, e, e, e, e], X). 
X = [[a, a, a, a], [b], [c, c], [a, a], [d], [e, e, e, e]] 
pack(L,X) 
*/ 
getHead([H|_], H).
get_all_consecutive(_,[],[], []). 
get_all_consecutive(E,[E|R],Res, Rem):- 
    get_all_consecutive(E,R,Res1,Rem), 
    append([E],Res1,Res). 
get_all_consecutive(_,L,[], L).
pack([],[]).
pack([H|R],Res):- 
    get_all_consecutive(H,[H|R],Chs,Rem),
    pack(Rem,Res1), 
    append([Chs],Res1,Res). 

enc(Cnt,E,[Cnt,E]). 
encode([],[]).
encode([H|R],Res):- 
  length(H,Cnt), 
  getHead(H,E), 
  enc(Cnt,E, EncodedH), 
  encode(R,Res1), 
  append([EncodedH],Res1,Res).