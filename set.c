/* Set.C

   By Michael W. Maher

   Ver 1.0 6/12/92      for MCS 5.1

   The following functions provide a general purpose SET.

   SET
	description:
		A simple mathematical structure that can hold things in
		no order and without duplicates.

	basic operators:
		add()
		set_del_elem()
		set_union()
		set_intersection()
		set_symmetric_difference()
		set_compare()
		is_an_element()
		is_empty()
		set_size()

	inialization:
		1. a ptr to the comparison function, the function must
		   return: a 0 if the two values are equal
			   a 1 if the first element is greater
			   a -1 if the first element is less than
		2. the ptr to the set must be set to NULL
		3. the set sturct elements must be set to zero
*/


/****************************************************************************
   function: add
 parameters: set     :a ptr to the set that the element will be added to
	     element :a ptr to the element to add to the set
    returns: if added successfully or duplicate was found and not added
	       TRUE
	     else
	       FALSE
    purpose: This function will add a single pointer to an (any) element
	     to a set of same-type elements.  The element will not be added
	     if one already exists in the set (no duplicates allowed).
****************************************************************************/
char add(set_type *setdata, void *element)
  {
  char    status = TRUE;
  dl_node *temp;

  if (is_an_element(setdata, element) == TRUE)
    {
    if (setdata->start == NULL)
      setdata->elements = 0L;
    status = TRUE;
    }
  else
    {
    /* insert the element at the start of the set list */
    if ((temp = (dl_node *) malloc(sizeof(dl_node))) != NULL)
      {
      if (setdata->start == NULL)
	setdata->elements = 0L;
      else
	setdata->start->prev = temp;
      temp->next = setdata->start;
      temp->prev = NULL;
      setdata->start = temp;
      temp->data = element;
      setdata->elements += 1;
      }
    else
      status = FALSE;
    }
  return(status);
  }


/****************************************************************************
   function: set_del_elem

 parameters: setdata : a ptr to the set that the element will be deleted from
	     element : a ptr to the element being deleted from the set
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: This function will remove an element from a set if it exists.
****************************************************************************/
char set_del_elem(set_type *setdata, void *element)
  {
  char   status = TRUE;

  if (is_an_element(setdata, element) == FALSE)
    status = FALSE;
  else
    {
    /* delete the element from the set list, curr_pos set by is_an_element */
    /* cases: no node: if is_an_element returns TRUE then there is a node
	      beginning: delete and point start to the new start node
	      middle: delete and set pointers
	      end: delete from the end, no extra work */
    /* is the current node the start? */
    if (setdata->curr_pos->prev == NULL)
      setdata->start = setdata->curr_pos->next;
    else
      setdata->curr_pos->prev->next = setdata->curr_pos->next;
    /* is the current node the last node? */
    if (setdata->curr_pos->next != NULL)
      setdata->curr_pos->next->prev = setdata->curr_pos->prev;
    free(setdata->curr_pos);
    setdata->elements -= 1;
    if (setdata->elements == 0)
      setdata->start = NULL;
    setdata->curr_pos = setdata->start;
    }
  return(status);
  }


/****************************************************************************
   function: set_union
 parameters: set1   :a ptr to a set of elements
	     set2   :a ptr to a set of elements
	     result :a set, the result of the union operation
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: This function will take the union of two sets. The union of a
	     set is the combined elements of two sets without duplicates.
	     The two operands should be of the same type, e.g. integers,
	     floats,....
****************************************************************************/
char set_union(set_type *set1, set_type *set2, set_type *result)
  {
  char     status = TRUE;
  dl_node  *temp;
  set_type *small,
	   *large;

  result->start    = NULL;
  result->comp_ele = set1->comp_ele;
  result->elements = 0L;

  /* to optimize this function find the smaller of the two sets first*/
  if (set1->elements <= set2->elements)
    {
    small = set1;
    large = set2;
    }
  else
    {
    small = set2;
    large = set1;
    }
  temp = small->start;
  while (temp != NULL)
    {
    if (is_an_element(large, temp->data) == FALSE)
      {
      if (add(result, temp->data) == FALSE)
	status = FALSE;
      }
    temp = temp->next;
    }
  temp = large->start;
  while ((temp != NULL) && (add(result, temp->data) == TRUE))
    {
    temp = temp->next;
    }
  if (temp != NULL)
    status = FALSE;
  return(status);
  }


/****************************************************************************
   function: set_intersection
 parameters: set1     - pointer to a set
	     set2     - a ptr to a set
	     result   - the intersection of set1 and set2
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: This function will take the intersection of two sets.
****************************************************************************/
char set_intersection(set_type *set1, set_type *set2, set_type *result)
  {
  char     status = TRUE;
  dl_node  *temp;
  set_type *small,
	   *large;

  result->start    = NULL;
  result->comp_ele = set1->comp_ele;
  result->elements = 0L;

  /* Optimize this function by find the smaller of the two sets first */
  if (set1->elements <= set2->elements)
    {
    small = set1;
    large = set2;
    }
  else
    {
    small = set2;
    large = set1;
    }
  temp = small->start;
  while (temp != NULL)
    {
    if (is_an_element(large, temp->data) == TRUE)
      {
      if (add(result, temp->data) == FALSE)
	status = FALSE;
      }
    temp = temp->next;
    }
  return(status);
  }


/****************************************************************************
   function: set_symmetric_difference
 parameters: set1     - pointer to a set
	     set2     - a ptr to a set
	     result   - the symmetric difference of set1 and set2
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: This routine performs the sysmetric difference on two sets.
	     This is the same thing as a "exclusive-or" function in
	     mathematics.
****************************************************************************/
char set_symmetric_difference(set_type *set1, set_type *set2, set_type *result)
  {
  char     status = TRUE;
  dl_node  *temp;
  set_type *small,
	   *large;

  result->start    = NULL;
  result->comp_ele = set1->comp_ele;
  result->elements = 0L;

  /* Optimize this function by find the smaller of the two sets first */
  if (set1->elements <= set2->elements)
    {
    small = set1;
    large = set2;
    }
  else
    {
    small = set2;
    large = set1;
    }
  temp = large->start;
  while (temp != NULL)
    {
    if (add(result, temp->data) == FALSE)
      status = FALSE;
    temp = temp->next;
    }
  temp = small->start;
  while (temp != NULL)
    {
    if (is_an_element(result, temp->data) == TRUE)
      set_del_elem(result, temp->data);
    else
      {
      if (add(result, temp->data) == FALSE)
	status = FALSE;
      }
    temp = temp->next;
    }
  return(status);
  }


/****************************************************************************
   function: set_compare
 parameters: set1
	     set2
    returns: if set1 is equal to set2 then TRUE
	     else FALSE
    purpose: This routine will compare two sets, element for element, for
	     equality.  If the set sizes are different or if any one
	     element of one set is not found in the other set then the two
	     sets are not equal.
****************************************************************************/
char set_compare(set_type *set1, set_type *set2)
  {
  char    equal = TRUE;
  dl_node *curr_element;

  if (set_size(set1) == set_size(set2))
    {
    curr_element = set2->start;
    do
      {
      curr_element = curr_element->next;
      }
    while ((curr_element != NULL) &&
	   (is_an_element(set1, curr_element) == TRUE));
    if (curr_element == NULL)
      equal = FALSE;
    }
  else
    equal = FALSE;
  return(equal);
  }




/****************************************************************************
   function: is_an_element
 parameters: setdata : a ptr to a set of elements
	     element : an element
    returns: if match is found
	       TRUE
	     else
	       FALSE
    purpose: The following routine will search the elements of a set to
	     find the matching element.  The comparison is performed by the
	     routine passed as a ptr in set comp_ele.  If a match is found
	     the curr_pos ptr is set to the match and TRUE is returned.
****************************************************************************/
char is_an_element(set_type *setdata, void *element)
  {
  dl_node *temp;

  temp = setdata->start;
  while ((temp != NULL) && ((*setdata->comp_ele)(temp->data, element) != 0))
    {
    temp = temp->next;
    }
  if (temp == NULL)
    return(FALSE);
  else
    {
    setdata->curr_pos = temp;
    return(TRUE);
    }
  }


/****************************************************************************
   function: is_empty
 parameters: set : the set to be tested
    returns: if empty set
	       TRUE
	     else
	       FALSE
    purpose: Use to determine if a set is empty, e.g. a set with no elements.
****************************************************************************/
char is_empty(set_type *setdata)
  {
  if (setdata->start == NULL)
    return(TRUE);
  else
    return(FALSE);
  }


/****************************************************************************
   function: set_size()

 parameters: setdata : a ptr to a set struct

    returns: The number of elements in the set. 0 is an empty set.

    purpose: The following function will return the size of a set.  The
	     size returned is an unsinged long integer.
****************************************************************************/
unsigned long set_size(set_type *setdata)
  {
  if (setdata->start == NULL)
    setdata->elements = 0L;
  return(setdata->elements);
  }


/****************************************************************************
   function: comp_integers()

 parameters: element1
	     element2

    returns: 1 is returned if element1 is greater than element2
	     0 is returned if element1 is equal to element2
	     -1 is returned if element1 is less than element2

    purpose: This function is an example of a user-defined function used
	     to compare to elements for equality. This function will
	     compare to integers for equality.
****************************************************************************/
char comp_integers(void *element1, void *element2)
  {
  if (*((unsigned *) element1) < *((unsigned *) element2))
    return(-1);
   else if (*((unsigned *) element1) > *((unsigned *) element2))
    return(1);
  else
    return(0);
  }

