/* LinkList.h

   By Michael W. Maher

   Ver 1.0 8/18/92      for MCS 5.1

   This is the header file for Set.C
   Programming tools written in Microsoft C ver 5.1.

   Linked-List functions and data types.

   ******************* Abstract Data Type Description (ADTD) ****************
   Linked List
	Properties:
		1. A doubly linked-list is the underlying structure
		2. A doubly linked list is simply a chain of data.  Each
		   data element is connected by a ptr to the one in front
		   of it and the one behind it.

	Operators:
		insert_before()
		insert_after()
		delete_curr()
		is_list_empty()
		list_size()
		list_start()
		list_end()
		list_next()
		list_previous()

	Data Types:
		dl_node : a doubly linked list node
		element : a void ptr to any data type
*/

#ifndef LLH
  #define LLH

  /* includes */
  #include<malloc.h>
  #include<stdlib.h>
  #include"toolkit.h"

  /****************************** macros ***********************************/

  /**************************** definitions ********************************/

  /********************* fundamental structure types ***********************/

  /************************* function prototypes ***************************/
  /* insert a data element into a list before current list position and
     decrement the list pointer to the previous position */
  char insert_before(dl_node *list, void *data);

  /* insert a data element into a list after current list position and
     advance the list pointer to the next position */
  char insert_after(dl_node *list, void *data);

  /* delete the current node from the list and return the ptr to the
     data element in the node, return NULL if unsuccessful */
  void *delete_curr(dl_node *list);

  /* check for an empty list: return TRUE if there are no data elements */
  char is_list_empty(dl_node *list);

  /* return the number of data elements in the list */
  unsigned long list_size(dl_node *list);

  /* set the list ptr position to the first element in the list */
  char list_start(dl_node *list);

  /* set the list ptr position to the last element in the list */
  char list_end(dl_node *list);

  /* set the list ptr position to the next element in the list */
  char list_next(dl_node *list);

  /* set the list ptr position to the previous element in the list */
  char list_previous(dl_node *list);

  #endif


