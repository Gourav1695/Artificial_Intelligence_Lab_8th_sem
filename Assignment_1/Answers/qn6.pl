 % 6. To find the sum and average of all elements of a list using sum and 
% length. 
 
sum_and_average(List, Sum, Average) :- 
    sum_list(List, Sum), 
    length(List, Length), 
    Average is Sum / Length. 
 
