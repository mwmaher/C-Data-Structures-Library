# mdqueue.c
A C library of general purpose data structures:

- Set
- Stack
- Queue
- Linked lists (single linked and doubly linked)


all code is ANSI standard C and originally developed under Microsoft C version 5.1.  All routines have been tested and debugged as well.  Source code and headers are fully documented.  I consider the programming style to be very readable and easy to follow (lots of white space).
	
The package that you are interested in could be described as a general-purpose set of programming tools that support three conceptual structures: sets, stacks, and queues.  I have worked up an abstract data type for linked lists but because I never needed it I never finished the code (I could finish it in about a day).  

Because the tools where written for maximum reusability the abstract data types (ADTDs: sets, stacks, and queues) can be used to store any data type without modification.  The queue tools support both a flat queue and a circular queue.  The sets, stacks, and queues are dynamic in nature and based on linked-lists (single and double);  therefore, the usage of available system memory is optimized.  For example, a programmer does not have to allocate a chunk of memory for every stack used under my stack ADTD (no more stack overflows).  Error checking is used extensively.

Actual header documentation:
******************* Abstract Data Type Description (ADTD) ****************

SET
Properties:
1. A set is a collection of things.
2. A set can have NO duplicates.
3. A set having no elements is an empty set.
4. The elements in a set have NO implied order.
5. A set has NO membership restrictions (except rule 6). e.g. sets of sets, sets of floats,...
6. A single set can not contain dissimilar types; e.g. a set with an integer, float, and a char.
   (It is possible to break this rule since it really is not a part of the mathematical definition.  With some creativity and a good reason to do so it could be done.)

Operators:
add()
delete()
set_union()
set_intersection()
set_symmetric_difference()
set_compare()
is_an_element()
is_empty()
set_size()
element_comparison_function()    NOTE: user defined function!

	Data Types:
sets: a set is a struct type set_type
elements: a void ptr to any data type   ******************* Abstract Data Type Description (ADTD) ****************

STACK
Properties:
1. A stack is LIFO structure (Last In First Out).  Elements are placed on and taken off from the stack only from the top of the stack.
2. This stack implementation is dynamic.  That is, it can grow and shrink in memory and does not require an up-front allocation.
3. The elements in a stack will remain in the order in which they were placed on the stack.
4. A set has NO membership restrictions; e.g. stacks of stacks, stacks of integers,...
	Operators:
push()
pop()
top()
stack_size()

Data Types:
stack    : a ptr to structure stack_type
element  : a ptr to any type placed on the stack


  ******************* Abstract Data Type Description (ADTD) ****************

QUEUE
Properties:
1) A queue is simple First In First Out (FIFO) structure.
2) The underlying structure is a doubly-linked list.
3) Memory for the linked list is dynamically allocated
   during the ENQUEUE process and deallocated during the
	DEQUEUE process.
4) RE-ENQUEUE is a special function used for creating circular queues.
Operators:
enqueue()
dequeue()
dequeue_re_enqueue()
get_next_from_queue()
init_queue()
release_all_data()
