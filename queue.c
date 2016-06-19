/* Queue.C

   By Michael W. Maher

   Ver 1.0 1/16/91
   Ver 2.0 6/5/92
   Ver 3.0 9/10/92      Improve mememory efficiency by utilizing single
			linked list instead of a doubly-linked list.

   The following functions provide QUEUE managment.

   QUEUE
     description:
	A queue is simple First In First Out (FIFO) structure.

	The underlying structure is a linked-list.

	Memory for the linked list is dynamically allowcated during the
	enqueue() process and deallocated during the dequeue() process.


     basic operators for manipulating queues:
	init_queue()
	get_queue_size()
	enqueue()
	dequeue()
	rotate_queue()
	flip_queue()
	release_all_data()


*/

/***************************************************************************
   function: enqueue()

 parameters:      data - pointer to data item to be put on queue.
		 queue - pointer to queue info.

    returns: if successful
	       return TRUE
	     else
	       return FALSE

    purpose: This function will add a data item to the queue.
****************************************************************************/
char enqueue(void *data, queue_rec *queue)
  {
  char    mem_found = TRUE;

  /* check for an empty queue condition */
  if (queue->ending == NULL)
    {
    if ((queue->ending = (l_node *) malloc(sizeof(l_node))) == NULL)
      mem_found = FALSE;               /* unsuccessful, return error */
    else
      {
      queue->beginning    = queue->ending;
      queue->ending->next = NULL;
      }
    }
  else
    {
    if ((queue->ending->next = (l_node *) malloc(sizeof(l_node))) == NULL)
      mem_found = FALSE;               /* unsuccessful, return error */
    else
      {
      queue->ending       = queue->ending->next;
      queue->ending->next = NULL;
      }
    }
  if (mem_found == TRUE)
    {
    queue->ending->data = data;
    queue->elements   += 1;
    }
  return(mem_found);
  }


/***************************************************************************
   function: dequeue()

 parameters:      data - A pointer a pointer to the data item to be removed
			 from the queue.
		 queue - pointer to queue info.

    returns: if the queue is empty
	       dequeue returns a FALSE
	       data is set to NULL
	     else
	       dequeue returns a TRUE
	       data is set to the last (oldest) data item in the queue

    purpose: Remove a data item (pointer) from the queue.
****************************************************************************/
char dequeue(void **data, queue_rec *queue)
  {
  char    data_found = TRUE;
  l_node *temp_node;

  /* check for an empty queue condition */
  if (queue->beginning != NULL)
    {
    temp_node = queue->beginning;
    *data     = temp_node->data;
    if (temp_node != queue->ending)
      {
      /* remove the node from the queue */
      queue->beginning = temp_node->next;
      free(temp_node);
      }
    else
      {
      /* remove the last item from the queue */
      free(temp_node);
      queue->ending    = NULL;
      queue->beginning = NULL;
      }
    queue->elements -= 1;
    }
  else
    {
    *data      = NULL;
    data_found = FALSE;
    }
  return(data_found);
  }


/***************************************************************************
   function: rotate_queue()

 parameters: queue - pointer to queue info.

    returns: TRUE  - if successful
	     FALSE - if not successful, or no items in the queue

    purpose: To rotate the items in a queue. The first-in item queue
	     becomes the last-in item in the queue.  Dumb but effective
	     analogy: The person at the beginning of the line is sent to
	     the end of the line at the movie theater.
****************************************************************************/
char rotate_queue(queue_rec *queue)
  {
  char    success = TRUE;
  l_node *temp_node;

  /* check for zero or one item in the queue - it saves time */
  if (queue->beginning != queue->ending)
    {
    temp_node           = queue->beginning;
    queue->ending->next = temp_node;
    queue->beginning    = temp_node->next;
    temp_node->next     = NULL;
    queue->ending       = queue->ending->next;
    }
  return(success);
  }


/***************************************************************************
   function: get_queue_size()

 parameters: queue - pointer to queue info.

    returns: The number of elements in the queue.

    purpose: Use to determine the number of elements in a queue.
****************************************************************************/
unsigned long get_queue_size(queue_rec *queue)
  {
  /* the number of elements is stored in queue.elements */
  return(queue->elements);
  }


/***************************************************************************
   function: init_queue()

 parameters: queue     - ptr to queue information

    returns: ptr the queue

    purpose: Set the queue information to NULL (the initial state).
***************************************************************************/
void *init_queue(queue_rec *queue)
  {
  queue->ending    = NULL;
  queue->beginning = NULL;
  queue->elements  = 0L;
  return(queue);
  }


/***************************************************************************
   function: flip_queue()

 parameters: queue - pointer to queue info.

    returns: TRUE  - if successful
	     FALSE - if not successful, or no items in the queue

    purpose: Reverses the order of the queue. The back of the queue
	     becomes the front.  This is a rather expense operation to
	     perform so use it wisely.
****************************************************************************/
char flip_queue(queue_rec *queue)
  {
  char    success = TRUE;
  l_node *temp;

  /* check for zero or one item in the queue - it saves time */
  if (queue->beginning != queue->ending)
    {
    reverse_l_list(queue->beginning);  /* reverse the ptrs in the list*/
    temp             = queue->ending;  /* swap the queue ptrs */
    queue->ending    = queue->beginning;
    queue->beginning = temp;
    if ((queue->beginning == NULL) || (queue->ending == NULL))
      success = FALSE;
    }
  return(success);
  }


/***************************************************************************
   function: release_all_data()

 parameters: queue - ptr to queue information structure

    returns: none

    purpose: Release all dynamically allocated memory back to system.
	     empty the entire queue.  This function can only be used with
	     items that have been created with malloc().  Do not use with
	     halloc() or any other allocation method.
****************************************************************************/
void release_all_data(queue_rec *queue)
  {
  struct collect_rec *data;

  while (dequeue((void **) &data, queue) == TRUE)
      free(data);
  return;
  }
