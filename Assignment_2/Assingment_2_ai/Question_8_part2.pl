 /*
Insertion sort 
for(int i=1;i<n; i++)
{ 
    int num = nums[i];
    int j = i-1;
    while(j>=0 && nums[j]>num)
    { 
        nums[j+1] = nums[j];
        j--; 
    } 
       nums[j+1] = num; 
    } 
       
insertion_sort(List,sortedList)
*/ 
insertion_sort(List, Result):- 
    i_sort(List,[], Result).
i_sort([],L, L).
i_sort([H|R],SortedList, Result):- 
    insert_in_sorted(H,SortedList,NewSortedList),
    i_sort(R,NewSortedList,Result). 

insert_in_sorted(E,[],[E]). insert_in_sorted(E,[H|R],Res):- 
    H<E,
    insert_in_sorted(E,R,Res1),
    append([H],Res1,Res). 
insert_in_sorted(E,[H|R],Res):- 
    H >= E, 
    append([E],[H|R],Res).