/* QueTest.C

   By Michael W. Maher

   Ver 1.0  9/20/91     First version of basic queue functions.
   Ver 1.5  9/1/92      Improved documentation.
   Ver 2.0  9/8/92      Rewritten for clarity, added new functionality.
   Ver 3.5  9/10/92     New queue functions were tested.

   QueTest.C is a set of test functions.  It tests the queue abstract
   data type.  QueTest.C tests the headers and functions in Queue.C and
   Queue.H.  Each related queue function is subjected to a battery of
   tests.  The queue routines either PASS or FAIL the tests.

   All routines were written in standard ANSI C.  To test for ANSI C
   compatibility the functions were compiled under MCS 5.1 with the /Za
   switch.  The /Za switch turns off all extensions to the language.

   NOTE: Be sure to allocate enough stack space when compiling.  20000 bytes
	 was sufficient for a TESTDATASIZE of 1000 when compiling with
	 Microsoft Ver 5.1. Example:

	 CL /Za QUETEST.C /link /STACK:20000
*/

/* include files */
/* Microsoft C Ver 5.1 headers */
#include <stdio.h>
#include <string.h>

/* Michael W. Maher - C headers */
#include "queue.h"                     /* queue management header */
#include "toolkit.h"                   /* misc functions header */

/* Michael W. Maher - C Source */
#include "queue.c"                     /* queue management source */
#include "toolkit.c"                   /* misc functions source */

/* defines */
#define TESTDATASIZE 1000L             /* the number of test elements */


/* function prototypes */
int  main(void);
char test1(FILE *output);
char test2(FILE *output);
char test3(FILE *output);
char test4(FILE *output);
char test5(FILE *output);
char *testout(char passfail, char *out);

int main(void)
  {
  FILE *output;
  char buf[5];

  output = stderr;                     /* direct output to a stream */
  fprintf(output, "\n\n"
		  "QUETEST.C By Michael W. Maher 9/1/92\n"
		  "Testing the Queue.C C function suite...\n\n");
  /* Perform an enqueue / dequeue operation ***********************/
  fprintf(output, "TEST #%d: %s\n", 1, testout(test1(output), buf));

  /* Test the get_queue_size() funtion ****************************/
  fprintf(output, "TEST #%d: %s\n", 2, testout(test2(output), buf));

  /* Test the rotate_queue() function *****************************/
  fprintf(output, "TEST #%d: %s\n", 3, testout(test3(output), buf));

  /* Test the flip_queue() function and the init_queue() function */
  fprintf(output, "TEST #%d: %s\n", 4, testout(test4(output), buf));

  /* Test the queue error handling abilities **********************/
  fprintf(output, "TEST #%d: %s\n", 5, testout(test5(output), buf));
  return(0);
  }


/****************************************************************************
   function: test1()

 parameters: directs output to a device

    returns: if the test exectued as expected - PASS
	     if the test did not execute properly - FAIL

    purpose: Performs an enqueue / dequeue test. Put data into the queue
	     and then remove the data from the queue.
****************************************************************************/
char test1(FILE *output)
  {
  char          test = PASS;
  char          error[81];
  unsigned long i,
		data_in[TESTDATASIZE],
		*data_out;
  queue_rec     my_queue;

  my_queue.ending = NULL;
  my_queue.beginning  = NULL;
  my_queue.elements = 0;
  for (i = 0; i<TESTDATASIZE; i++)
    {
    data_in[i] = i;
    if (enqueue(&data_in[i], &my_queue) == FALSE)
      {
      fprintf(output,"enqueue: failed, #%lu\n", i);
      test = FAIL;
      }
    }
  printf("\n");
  for (i = 0; i<TESTDATASIZE; i++)
    {
    if ((dequeue((void **) &data_out, &my_queue) == FALSE) ||
	(*data_out != i))
      {
      fprintf(output,"dequeue: failed, #%lu\n", i);
      test = FAIL;
      }
    }
  return(test);
  }


/****************************************************************************
   function: test2()

 parameters: output - directs output to a device

    returns: if the test exectued as expected - PASS
	     if the test did not execute properly - FAIL

    purpose: This function tests the get_queue_size() funtion. It puts
	     (i) elements into the queue then checks the number reported.
	     Then it removes the elements from the queue an checks the
	     number reported again; the number should be zero.
****************************************************************************/
char test2(FILE *output)
  {
  char          test = PASS;
  unsigned long i,
		data_in[TESTDATASIZE],
		*data_out;
  queue_rec     my_queue;

  my_queue.ending = NULL;
  my_queue.beginning  = NULL;
  my_queue.elements = 0;
  for (i = 0; i<TESTDATASIZE; i++)
    {
    data_in[i] = i;
    if (enqueue(&data_in[i], &my_queue) == FALSE)
      {
      fprintf(output,"enqueue: failed, #%lu\n", i);
      test = FAIL;
      }
    }
  /* Test for the proper number of elements after queuing up. */
  if (get_queue_size(&my_queue) != i)
    test = FAIL;
  for (i = 0; i<TESTDATASIZE; i++)
    {
    if ((dequeue((void **) &data_out, &my_queue) == FALSE) ||
		 (*data_out != i))
      {
      fprintf(output,"dequeue: failed, #%lu\n", i);
      test = FAIL;
      }
    }
  /* Test for the proper number of elements after removing all of them */
  if (get_queue_size(&my_queue) != 0L)
    test = FAIL;
  return(test);
  }


/****************************************************************************
   function: test3()

 parameters: output - directs output to a device

    returns: if the test exectued as expected - PASS
	     if the test did not execute properly - FAIL

    purpose: This function will test the rotate_queue() function. First,
	     a queue is filled with consecutive integers. Then every other
	     integer is removed. The remaining integers should be only
	     the odd integers. The function then verifies this.
****************************************************************************/
char test3(FILE *output)
  {
  char          test = PASS;
  unsigned long i,
		data_in[TESTDATASIZE],
		*data_out;
  queue_rec     my_queue;

  /* initialize the queue structure - testing the initialize function later */
  my_queue.ending = NULL;
  my_queue.beginning  = NULL;
  my_queue.elements = 0;
  /* build a queue of integers in order from 0 to TESTDATASIZE - 1*/
  for (i = 0; i<TESTDATASIZE; i++)
    {
    data_in[i] = i;
    if (enqueue(&data_in[i], &my_queue) == FALSE)
      {
      fprintf(output,"enqueue: failed, #%lu\n", i);
      test = FAIL;
      }
    }
  /* remove all even numbers by removing then rotating */
  for (i = 0; i < TESTDATASIZE; i += 2)
    {
    if (dequeue((void **) &data_out, &my_queue) == FALSE)
      {
      printf("dequeue 1: failed, #%lu\n", i);
      test = FAIL;
      }
    else
      {
      if (rotate_queue(&my_queue) == FALSE)
	{
	fprintf(output,"rotate_queue: failed, #%lu\n", i);
	test = FAIL;
	}
      }
    }
  /* test for only odds remaining */
  for (i = 1; i < TESTDATASIZE; i += 2)
    {
    if ((dequeue((void **) &data_out, &my_queue) == FALSE) ||
		 (*data_out != i))
      {
      fprintf(output,"dequeue 2: failed, #%lu != %lu\n", i, *data_out);
      test = FAIL;
      }
    }
  /* Test for the proper number of elements after removing all of them */
  if (get_queue_size(&my_queue) != 0L)
    test = FAIL;
  return(test);
  }


/****************************************************************************
   function: test4()

 parameters: output - directs output to a device

    returns: if the test exectued as expected - PASS
	     if the test did not execute properly - FAIL

    purpose: This function will test the flip_queue() function. First,
	     a queue is filled with consecutive integers.  Then the queue
	     is flipped (turned over) with flip_queue().  The numbers will
	     dequeue() in the reverse order (behaving in a stack-like
	     fashion).
****************************************************************************/
char test4(FILE *output)
  {
  char          test = PASS;
  unsigned long data_in[TESTDATASIZE],
		*data_out,
		i;
  queue_rec     my_queue;

  init_queue(&my_queue);
  /* build a queue of integers in order from 0 to TESTDATASIZE - 1*/
  for (i = 0; i<TESTDATASIZE; i += 1)
    {
    data_in[i] = i;
    if (enqueue(&data_in[i], &my_queue) == FALSE)
      {
      fprintf(output, "enqueue: failed, #%lu\n", i);
      test = FAIL;
      }
    }
  /* reverse the order of the queue */
  if (flip_queue(&my_queue) == FALSE)
    {
    fprintf(output, "The queue flip failed.\n");
    test = FAIL;
    }
  /* test for the reversed order of the integers */
   for (i = TESTDATASIZE; i > 0L; i -= 1L)
    {
    if ((dequeue((void **) &data_out, &my_queue) == FALSE) ||
		 (*data_out != (i-1)))
      {
      fprintf(output, "dequeue: failed, #%lu != %lu\n", i, *data_out);
      test = FAIL;
      }
    }
  /* Test for the proper number of elements after removing all of them */
  if (get_queue_size(&my_queue) != 0L)
    {
    test = FAIL;
    fprintf(output, "queue size different than expected: %lu\n",
	    get_queue_size(&my_queue));
    }
  return(test);
  }


/****************************************************************************
   function: test5()

 parameters: output - directs output to a device

    returns: if the test exectued as expected - PASS
	     if the test did not execute properly - FAIL

    purpose: The following function will test the queue limits.
****************************************************************************/
char test5(FILE *output)
  {
  char          test = PASS,
		*data;
  queue_rec     my_queue;

  /* initialize the queue */
  init_queue(&my_queue);
  /* try to do a dequeue() operation on an empty queue */
  if (dequeue((void **) &data, &my_queue) != FALSE)
    {
    test = FAIL;
    fprintf(output,"Dequeue: Failed to trap empty queue error.\n");
    }
  /* try to do a get_queue_size() operation on an empty queue */
  if (get_queue_size(&my_queue) != 0L)
    {
    test = FAIL;
    fprintf(output,"get_queue_size: non-zero returned for an empty queue.\n");
    }
  /* try to do a flip_queue() operation on an empty queue */
  if (flip_queue(&my_queue) != TRUE)
    {
    test = FAIL;
    fprintf(output,"flip_queue: Empty queue detected as an error.\n");
    }
  return(test);
  }


/****************************************************************************
   function: testout()

 parameters: passfail - boolean value (PASS or FAIL)
		  out - 5 character string

    returns: "PASS" is returned in the string (out) if passfail contains
	     a PASS char value.
	     "FAIL" is returned in the string (out) if passfail contains
	     a FAIL char value.

    purpose: This function converts a boolean value to a string value.
****************************************************************************/
char *testout(char passfail, char *out)
  {
  if (passfail == PASS)
    strcpy(out, "PASS");
  else
    strcpy(out, "FAIL");
  return(out);
  }
