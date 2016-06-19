/* Stack.h

   By Michael W. Maher

   Ver 1.0 6/12/92      for MCS 5.1
   Ver 1.5 8/18/92

   This is the header file for stack.C

   Testing was performed under the Microsoft C ver 5.1 environment.

   Stack functions and data types.

   ******************* Abstract Data Type Description (ADTD) ****************
   STACK
	Properties:
		1. A stack is LIFO structure (Last In First Out).  Elements
		   are placed on and taken off from the stack only from the
		   top of the stack.
		2. This stack implementation is dynamic.  That is, it can
		   grow and shrink in memory and does not require an
		   up-front allocation.
		3. The elements in a stack will remain in the order in
		   which they were placed on the stack.
		4. A set has NO membership restrictions.
		   e.g. stacks of stacks, stacks of integers,...

	Operators:
		push()
		pop()
		top()
		get_stack_size()
		init_stack()
		flip_stack()

	Data Types:
		stack    : a ptr to structure stack_type
		element  : a ptr to an any data type
*/

#ifndef STACKH
  #define STACKH

  /******************************* includes ********************************/
  #include<malloc.h>
  #include<stdlib.h>
  #include"toolkit.h"

  /******************************** macros *********************************/


  /*********************** fundamental structure types *********************/

  /* stack data type */
  typedef struct stack_type
    {
    l_node        *top;                 /* a ptr to the top element */
    l_node        *bottom;              /* a ptr to the bottom element */
    unsigned long elements;             /* the number of stack elements*/
    } stack_type;


  /*************************** stack functions *****************************/

  /* place an element onto the stack */
  char push(stack_type *stack, void *data);

  /* remove the last item (last item pushed) from the stack */
  char pop(stack_type *stack, void **data);

  /* return but do not remove the last item pushed onto the stack */
  char top(stack_type *stack, void **data);

  /* return the number of elements on the stack */
  char get_stack_size(stack_type *stack, unsigned long *elements);

  /* initialize the stack for use */
  void init_stack(stack_type *stack);

  /* Flip the stack over. Reverse the order of the elements */
  char flip_stack(stack_type *stack);
  #endif
