% 7. % Base case: GCD of a number and 0 is the number itself. 
gcd(X, 0, X) :- X > 0. 
gcd(0, Y, Y) :- Y > 0. 
% Recursive case: GCD using the Euclidean algorithm. 
gcd(X, Y, GCD) :- 
    X > 0, 
    Y > 0, 
    X >= Y, 
    Z is X mod Y, 
    gcd(Y, Z, GCD). 
 
gcd(X, Y, GCD) :- 
    X > 0, 
    Y > 0, 
    X < Y, 
    gcd(Y, X, GCD). 