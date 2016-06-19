/* StakTest.C

   By Michael W. Maher

   Ver 1.0 6/12/92      for MCS 5.1
   Ver 2.0 9/1/92       Improved the documentation of StaKTest.C


   The following will test the general purpose STACK functions found in
   STACK.C and STACK.H.

   The function is ANSI C complient.  It was tested for complience with
   the Microsoft C compiler V5.51 using the /Za switch.  Also, when
   compiling with TEST_SIZE set to a large value, like 1000, be sure to
   increase the default stack size used.  MSC5.1 compiling example:

	CL /Za SETTEST.C /link /STACK:36000


   Notes: A stack is a simple LIFO structure with a few basic operators:
	push
	pop
	top
	stack_size
*/
/******************************** defines **********************************/
#define TEST_SIZE 1000

/*********************** ANSI C standard libraries *************************/
#include<stdio.h>
#include<string.h>

/********************* Headers By Michael W. Maher *************************/
#include"toolkit.h"
#include"stack.h"

/********************* C source By Michael W. Maher ************************/
#include"toolkit.c"
#include"stack.c"

/*************************** Function Prototypes ***************************/
void main(void);
char test1(FILE *output);
char test2(FILE *output);
char test3(FILE *output);
char *testout(char passfail, char *out);


void main()
  {
  FILE *output;
  char buf[5];

  output = stdout;                     /* direct output to the screen */

  fprintf(output, "\n\n"
		  "staktest.c By Michael W. Maher 9/1/92\n"
		  "Testing the stack.c C functions...\n\n");

  /* Performs a stack push() and pop() test. */
  fprintf(output, "TEST #%d: %s\n", 1, testout(test1(output), buf));

  /* Test the flip_stack() & init_stack() functions */
  fprintf(output, "TEST #%d: %s\n", 2, testout(test2(output), buf));

  /* Test the get_stack_size() function */
  fprintf(output, "TEST #%d: %s\n", 3, testout(test3(output), buf));
  return;
  }



/****************************************************************************
   function: test1()

 parameters: output - directs output to a device

    returns: PASS if the test was successful
	     FAIL if the test did not work properly

    purpose: This function will test the push() and pop() stack functions.
****************************************************************************/
char test1(FILE *output)
  {
  char          test = PASS;
  stack_type    test_stack;
  unsigned long i,
		j[TEST_SIZE],
		*buff;

  /* initialize the stack */
  test_stack.top = NULL;
  /* put sequential integers into the stack */
  for(i = 0; i < TEST_SIZE; i++)
    {
    j[i] = i;
    if (push(&test_stack, &j[i]) == FALSE)
      {
      fprintf(output, "ERROR 1: push\n");
      test = FAIL;
      }
    }
  /* verify that the stack has the correct integers in order */
  for(i = TEST_SIZE - 1; i > 0; i--)
    {
    if ((pop(&test_stack, (void **) &buff) == FALSE) || (*buff != i))
      {
      fprintf(output, "ERROR 2: pop #%lu\n", i);
      test = FAIL;
      }
    }
  return(test);
  }


/****************************************************************************
   function: test2()

 parameters: output - directs output to a device

    returns: PASS if the test was successful
	     FAIL if the test did not work properly

    purpose: This function will test the flip_stack and init_stack() stack
	     functions.
****************************************************************************/
char test2(FILE *output)
  {
  char          test = PASS;
  stack_type    test_stack;
  unsigned long i,
		j[TEST_SIZE],
		*buff;

  init_stack(&test_stack);             /* initialize the stack */
  /* put sequential integers into the stack */
  for(i = 0; i < TEST_SIZE; i++)
    {
    j[i] = i;
    if (push(&test_stack, &j[i]) == FALSE)
      {
      fprintf(output, "ERROR 1: push, %lu\n", i);
      test = FAIL;
      }
    }
  /* reverse the order of the stack - flip it over */
  if (flip_stack(&test_stack) == FALSE)
    {
    fprintf(output, "Stack flip failed.\n");
    test = FAIL;
    }
  /* verify that the stack has the correct integers in order */
  for(i = 0; i < TEST_SIZE; i++)
    {
    if ((pop(&test_stack, (void **) &buff) == FALSE) || (*buff != i))
      {
      fprintf(output, "ERROR 2: pop #%lu != %lu\n", i, *buff);
      test = FAIL;
      }
    }
  return(test);
  }


/****************************************************************************
   function: test3()

 parameters: output - directs output to a device

    returns: PASS if the test was successful
	     FAIL if the test did not work properly

    purpose: This function will test the get_stack_size() stack functions.
****************************************************************************/
char test3(FILE *output)
  {
  char test = PASS;

  if (test == FAIL)
    fprintf(output, "ERROR: test 3 - ");
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

