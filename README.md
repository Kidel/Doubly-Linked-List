# Doubly Linked List
An old C++ homework from my first year at University

Expected output:
```
Empty list <int>
[ ]
Is it empty? True

pushFront 1 and 0, then pushBack 2
[ 0; 1; 2 ]
From cout: [ 0; 1; 2 ]
is it empty? False

popFront
[ 1; 2 ]
popFront
[ 2 ]
popFront
[ ]

pushFront 0, then pushBack 1 and 2
[ 0; 1; 2 ]

popBack
[ 0; 1 ]
popBack
[ 0 ]
popBack
[ ]

insert 0 in position 2
[ 0 ]
insert 1 in position 2
[ 0; 1 ]
insert 2 in position 2
[ 0; 1; 2 ]
insert 3 in position 2
[ 0; 1; 3; 2 ]
insert 4 in position 2
[ 0; 1; 4; 3; 2 ]

erase in position 2
[ 0; 1; 3; 2 ]
erase in position 2
[ 0; 1; 2 ]
erase in position 2
[ 0; 1 ]
erase in position 2
[ 0; 1 ]
erase in position 2
[ 0; 1 ]

The index of element 1 is 1
The index of element 0 is 0
The index of element 2 is -1
pushBack 5
[ 0; 1; 5 ]
insert 5 in position 2
[ 0; 1; 6; 5 ]
The index of element 6 is 2


Empty list <string>
[ ]
pushFront "one" and "zero", then pushBack "two"
[ zero; one; two ]


Another list <int>
[ 1; 1; 1 ]


A list of lists of <int>
[ ]

pushFront of the 2 <int> lists previously created
[ [ 1; 1; 1 ]; [ 0; 1; 6; 5 ] ]


Press any key to exit...
```
