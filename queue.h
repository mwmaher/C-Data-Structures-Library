/* Queue.H

   By Michael W. Maher

   Ver 1.0 4/5/91       MCS 5.1
   Ver 1.5 8/18/92
   Ver 2.0 9/10/92      A change was made to the queue structure to make
			it more efficient.  It now uses a linked-list
			instead of a doubly linked list.

   DESCRIPTION: The header is for QueFunc.c

   Queue functions and data types.

   ******************* Abstract Data Type Description (ADTD) ****************
   QUEUE
	Properties:
		1) A queue is simple First In First Out (FIFO) structure.
		2) Items are added to the back of the queue.
		3) Items are removed from the front of the queue.
		4) The underlying structure is a linked list.
		5) Memory for the linked list is dynamically allocated
		   during the ENQUEUE process and deallocated during the
		   DEQUEUE process.

	Operators:
		enqueue()
		dequeue()
		init_queue()
		get_queue_size()
		release_all_data()

	Data Types:
		queue_rec
		data
*/

#ifndef MQUEUEH
  #define MQUEUEH

  /******************************* includes ********************************/
  #include<malloc.h>
  #include<stdio.h>
  #include<stdlib.h>
  #include"toolkit.h"


  /********************************* macros ********************************/
  #ifndef CHAR_SIZE
    #define CHAR_SIZE sizeof(char)
  #endif

  #ifndef UNSIGNED_LONG_SIZE
    #define UNSIGNED_LONG_SIZE sizeof(unsigned long)
  #endif

  /****************************** definitions ******************************/


  /********************structures and type definitions *********************/
  /* the general queue structure: could support a flat, circular... */
  typedef struct queue_rec
    {
    l_node       *ending;              /* end of the line, new element */
    l_node       *beginning;           /* begining of the line, oldest */
    unsigned long elements;            /* # of current elements in list */
    } queue_rec;


  /************************* function prototypes ***************************/
  /* to add an item to the queue */
  char enqueue(void *data_ptr, queue_rec *queue);

  /* to remove an item from the queue */
  char dequeue(void **data_ptr, queue_rec *queue);

  /* returns the number of elements in the queue */
  unsigned long get_queue_size(queue_rec *queue);

  /* move the first-in element to the last-in position */
  char rotate_queue(queue_rec *queue);

  /* initializes a queue structure */
  void *init_queue(queue_rec *queue);

  /* reverse the order of the queue */
  char flip_queue(queue_rec *queue);

  /* properly destroys a queue filled with items created with alloc(). */
  void release_all_data(queue_rec *queue);

#endif
