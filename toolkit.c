/* ToolKit.C

   By Michael W. Maher

   Ver 1.0 4/5/91       for MCS 5.1
   Ver 1.5 5/5/92

   Miscellaneous programming tools written in Microsoft C ver 5.1.  All of
   the following functions conform to ANSI C standards for optimum
   portability and reusability.
*/


/**************************** linked lists *********************************/

/***************************************************************************
   function: reverse_dl_list()

 parameters: list - ptr to doubly-linked list node

    returns: none

    purpose: This routine will reverse the prev and next pointers in a
	     doubly linked list. This effectively reverses the direction
	     of the list.  The use of temp in the first 3 lines of code
	     is for speed optimization not clarity - the author feels it
	     was justifyable change.
****************************************************************************/
void reverse_dl_list(dl_node *list)
  {
  dl_node *temp = list->next;

  if (temp != NULL)
    reverse_dl_list(temp);
  list->next = list->prev;
  list->prev = temp;
  return;
  }


/***************************************************************************
   function: reverse_l_list()

 parameters: list - ptr to the start of a linked list

    returns: none

    purpose: This routine will reverse the prev and next pointers in a
	     linked list.  This effectively reverses the direction of the
	     list.
****************************************************************************/
void reverse_l_list(l_node *list)
  {
  if ((list->next != NULL) && (list->next->next != NULL))
    reverse_l_list(list->next);
  list->next->next = list;
  list->next       = NULL;
  return;
  }


/* a template for function header */
/****************************************************************************
   function:
 parameters:
    returns:
    purpose:
****************************************************************************/

