% 4. To determine whether a list is a palindrome. 
 % is_palindrome(List) :- 
%     reverse(List, List). 
 
% Alternative implementation without using reverse/2 
 is_palindrome(List) :- 
    palindrome_check(List, []). 
 
 palindrome_check([], List). 
 palindrome_check([X|Xs], Acc) :- 
     palindrome_check(Xs, [X|Acc]).