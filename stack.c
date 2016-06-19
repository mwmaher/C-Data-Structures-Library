/* Stack.C

   By Michael W. Maher

   Ver 1.0 5/21/92      first version of basic stack routines
   Ver 1.1 6/12/92

   The following functions provide the tools to manipulate a general
   purpose dynamically allocated stack in memory. With this implementation
   the programmer does not have to allocate memory for a stack.  Therefore,
   The stack can grow to any size, constrained only by available system
   memory.  A dynamic stack does not overflow!


   STACK
	description:
		1) A stack is a simple LIFO structure - Last In First Out
		2) items are put onto the stack with the push operator
		3) itmes are removed from the stack with the pop operator

	basic operators:
		push()          : put an element on to the stack
		pop()           : remove an elment from the top
		top()           : return without removing the top element
		get_stack_size(): return the number of stack elements
		flip_stack()    : flip the stack over
		init_stack()    : initialize the queue

	inialization:
		init_stack()
*/


/****************************************************************************
   function: push
 parameters:  data - a pointer to the data item to be put on the stack.
	     stack - pointer to the stack
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: put a pointer (to data of any type) onto the top of the stack.
****************************************************************************/
char push(stack_type *stack, void *data)
  {
  char mem_found = TRUE;
  l_node *temp;

  if (stack->top == NULL)
    {
    if ((stack->top = (l_node*) malloc(sizeof(l_node))) == NULL)
      mem_found = FALSE;
    else
      {
      stack->top->data = data;
      stack->top->next = NULL;
      stack->bottom    = stack->top;
      stack->elements  = 1L;
      }
    }
  else
    {
    if ((temp = (l_node*) malloc(sizeof(l_node))) == NULL)
      mem_found = FALSE;
    else
      {
      temp->data       = data;
      temp->next       = stack->top;
      stack->top       = temp;
      stack->elements += 1;
      }
    }
  return(mem_found);
  }


/****************************************************************************
   function: pop
 parameters: stack - pointer to the stack device
	      data - a pointer to data removed from the top of the stack
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: remove a pointer (to data of any type) from the top of the stack.
****************************************************************************/
char pop(stack_type *stack, void **data)
  {
  char mem_found = TRUE;
  l_node *temp;

  if (stack->top == NULL)
    mem_found = FALSE;
  else
    {
    *data = stack->top->data;
    if (stack->top->next != NULL)
      {
      temp = stack->top;
      stack->top = stack->top->next;
      free(temp);
      stack->elements -= 1;
      }
    else
      {
      free(stack->top);
      init_stack(stack);
      }
    }
  return(mem_found);
  }


/****************************************************************************
   function: top
 parameters: stack - pointer to the stack device
	      data - a pointer to the data item on the top of the stack
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: Pulls the top data item from the stack.  A pointer (to data
	     of any type) from the top of the stack. This routine only works
	     with stacks created from stack_type. Not the system stack!!!
****************************************************************************/
char top(stack_type *stack, void **data)
  {
  char mem_found = TRUE;

  if (stack->top == NULL)
    mem_found = FALSE;
  else
    *data = stack->top->data;
  return(mem_found);
  }


/****************************************************************************
   function: get_stack_size
 parameters: stack - pointer to the stack device
	     elements - a pointer to the number of data items on the stack
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: Allows the user to quickly find out how many elements are on
	     the stack.
****************************************************************************/
char get_stack_size(stack_type *stack, unsigned long *elements)
  {
  if ((*elements == 0L) && (stack->top != NULL))
    {
    *elements = 0L;
    return(FALSE);
    }
  else
    *elements = stack->elements;
  return(TRUE);
  }


/****************************************************************************
   function: flip_stack

 parameters: stack - pointer to the stack device

    returns: if successful
	       TRUE
	     else
	       FALSE

    purpose: The following routine will reverse the order of elements in
	     the stack.  Please note that it uses an efficient recursive
	     algorithm.  So be carefull when using this.
****************************************************************************/
char flip_stack(stack_type *stack)
  {
  l_node *temp;
  char   success = TRUE;

  if (stack->top != NULL)
    {
    reverse_l_list(stack->top);
    temp          = stack->top;
    stack->top    = stack->bottom;
    stack->bottom = temp;
    }
  else
    success = FALSE;
  return(success);
  }


/****************************************************************************
   function: init_stack

 parameters: stack - pointer to the stack device

    returns: if successful
	       TRUE
	     else
	       FALSE

    purpose: Initializes the stack for use.
****************************************************************************/
void init_stack(stack_type *stack)
  {
  stack->top      = NULL;
  stack->bottom   = NULL;
  stack->elements = 0L;
  return;
  }




