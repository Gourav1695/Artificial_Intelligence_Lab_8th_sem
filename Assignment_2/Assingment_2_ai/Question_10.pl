* Database Predicates */ 
store(best_smoothies, [alan,john,mary], 
[ smoothie(berry, [orange, blueberry, strawberry], 2), smoothie(tropical, [orange, banana, mango, guava], 3), smoothie(blue, [banana, blueberry], 3) ]).
 store(all_smoothies, [keith,mary], [ smoothie(pinacolada, [orange, pineapple, coconut], 2), 
 smoothie(green, [orange, banana, kiwi], 5), 
 smoothie(purple, [orange, blueberry, strawberry], 2), smoothie(smooth, [orange, banana, mango],1) ]). 
 store(smoothies_galore, [heath,john,michelle],[ smoothie(combo1, [strawberry, orange, banana], 2), smoothie(combo2, [banana, orange], 5), 
 smoothie(combo3, [orange, peach, banana], 2), 
 smoothie(combo4, [guava, mango, papaya, orange],1), smoothie(combo5, [grapefruit, banana, pear],1) ]).
 
  /* a) Write a Prolog predicate more_than_four(X) that is true if store X has four or more smoothies on its menu. For instance: ?- more_than_four(best_smoothies). No ?- more_than_four(X). X = all_smoothies ; X = smoothies_galore ; No */ 
  
  more_than_four(X):- store(X,_,Smoothies),
length(Smoothies,Len), Len>=4. /* b)
 Write a Prolog predicate exists(X) that is true if there is a store that sells a smoothie named X. For instance: ?- exists(combo1). Yes ?- exists(slimy). No ?- exists(X). X = berry ; X = tropical <enter> Yes */ exists(X):- store(_,_,Smoothies), member(smoothie(X,_,_),Smoothies).
/* c) Write a Prolog predicate ratio(X,R) that is true if there is a store named X, and if R is the ratio of the store's number of employees to the store's number of smoothies on the menu. For instance: ?- ratio(all_smoothies,R). R = 0.5 ; No ?- ratio(Store,R). Store = best_smoothies R = 1 ; Store = all_smoothies R = 0.5 ; Store = smoothies_galore R = 0.6 ; No Hint you may need to define a helper predicate to implement ratio */ 
ratio(X,R):-
store(X,Emplist,Smoothielist), length(Emplist, No_of_Employees), length(Smoothielist,No_of_Smoothies), R is No_of_Employees/No_of_Smoothies. 
/* d) Write a Prolog predicate average(X,A) that is true if there is a store named X, and if A is the average price of the smoothies on the store's menu. For instance: ?- average(best_smoothies,A). A = 2.66667 ; No */ 
price(smoothie(_,_,Price),Price). sumup([],0). sumup([H|R], Sum):- price(H,Price), sumup(R,Sum2), Sum is Price + Sum2. average(X,A):- store(X,_,SmoothieList),
sumup(SmoothieList,Sum), length(SmoothieList,No_of_smoothies), A is Sum/No_of_smoothies. 
/* e) Write a Prolog predicate smoothies_in_store(X,L) that is true if there is a store named X, and if L is the list of smoothie names on the store's menu. For instance: ?- smoothies_in_store(all_smoothies,L). L = [pinacolada, green, purple, smooth] ; No ?- smoothies_in_store(Store,L). Store = best_smoothies L = [berry, tropical, blue] ; Store = all_smoothies L = [pinacolada, green, purple, smooth] ; Store = smoothies_galore L = [combo1, combo2,
combo3, combo4, combo5] ; No */ 

getName(smoothie(Name,_,_),Name). getSmoothieNames([],[]). getSmoothieNames([H|R], Res):- getName(H,Name), getSmoothieNames(R,Res1), append([Name],Res1,Res). smoothies_in_store(X,L):- store(X,_,SmoothieList), getSmoothieNames(SmoothieList,L). /* f) Write a Prolog predicate fruit_in_all_smoothies(X,F) that is true if there is a fruit F that is an ingredient of all smoothies on the menu of store X. For instance: ?- fruit_in_all_smoothies(Store,orange). Store = all_smoothies ;
No */ is_in(F,smoothie(_,Lof,_)):- member(F,Lof). is_present(_,[]). is_present(F,[H|R]):- is_in(F,H), is_present(F,R). fruit_in_all_smoothies(X,F):- store(X,_,SmoothieList), is_present(F,SmoothieList).