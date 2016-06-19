/* settest.c

   By Michael W. Maher

   Ver 1.0 6/15/92      for MCS 5.1

   The following program will test the general purpose SET functions.
   These functions are found in the SET.H header file.  The source code
   is located in SET.C.

   The function is ANSI C complient.  It was tested for complience with
   the Microsoft C compiler V5.51 using the /Za switch. Example:

	CL /Za settest.c

   SET
	description:
		A simple data structure.
		No ordering or interelationships between elements is implied.

	basic operators:
		add()
		set_del_elem()
		union()
		intersection()
		symmetric_difference()
		set_compare
		is_an_element()
		is_empty()

	intialization:
		1. a ptr to the comparison function
		2. the ptr to the set must be set to NULL
*/


/******************************** includes *********************************/
#include<stdio.h>
#include<string.h>
#include"set.h"
#include"set.c"

#define MAX_SET 20

/**************************** function prototypes **************************/
void main(void);
char test_1(FILE *output);
char test_2(FILE *output);
char test_3(FILE *output);
char test_4(FILE *output);
char *testout(char passfail, char *out);
char comp_integers(void *element1, void *element2);

void main()
  {
  FILE *output;
  char buf[5];

  output = stderr;                     /* direct output to a stream */
  fprintf(output, "\n\n"
		  "SETTEST.C By Michael W. Maher 9/1/92\n"
		  "Testing the SET.C C function suite...\n\n");

  /* Test the set add() and set_del_elem() operators. */
  fprintf(output, "TEST #%d: %s\n", 1, testout(test_1(output), buf));

  /* Test the set union operator. */
  fprintf(output, "TEST #%d: %s\n", 2, testout(test_2(output), buf));

  /* Test the set intersection operator. */
  fprintf(output, "TEST #%d: %s\n", 3, testout(test_3(output), buf));

  /* Test the set symetric difference operator. */
  fprintf(output, "TEST #%d: %s\n", 4, testout(test_4(output), buf));
  }


/****************************************************************************
   function: test_1
 parameters:
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: Tests the adding and removing of elements from a set.
****************************************************************************/
char test_1(FILE *output)
  {
  char status = PASS;
  set_type my_set;
  unsigned i,
	   j[MAX_SET];

  my_set.start = NULL;
  my_set.comp_ele = comp_integers;

  if (is_empty(&my_set) == FALSE)
    {
    fprintf(output,"ERROR: Set is not empty\n");
    status = FAIL;
    }
  /* add integers to a set */
  for (i = 0; i < MAX_SET; i++)
    {
    j[i] = i;
    if (add(&my_set, &j[i]) == FALSE)
      {
      fprintf(output,"ERROR: add not working, %d, elements:%ld\n",
	      i, my_set.elements);
      status = FAIL;
      }
    }
  if (is_empty(&my_set) == TRUE)
    {
    fprintf(output,"ERROR: Set is empty after elements added.\n");
    status = FAIL;
    }
  /* check to make sure all the even elements are there, remove each one*/
  for (i = 0; i < MAX_SET; i += 2)
    {
    if (is_an_element(&my_set, &i) == FALSE)
      {
      fprintf(output,"ERROR: Unknown element, %d\n", i);
      status = FAIL;
      }
    if (set_del_elem(&my_set, &i) == FALSE)
      {
      fprintf(output,"Delete not working, %d\n", i);
      status = FAIL;
      }
    }
  /* check to make sure all the odds are there, remove each one */
  for (i = 1; i < MAX_SET; i += 2)
    {
    if (is_an_element(&my_set, &i) == FALSE)
      {
      fprintf(output,"ERROR: not an element, %d\n", i);
      status = FAIL;
      }
    if (set_del_elem(&my_set, &i) == FALSE)
      {
      fprintf(output,"ERROR: set_del_elem() no working, %d\n", i);
      status = FAIL;
      }
    }
  /* check to make sure that the set is empty */
  if (is_empty(&my_set) == FALSE)
    {
    fprintf(output,"ERROR: The set is not empty.\n");
    status = FAIL;
    }
  return(status);
  }


/****************************************************************************
   function: test_2
 parameters: none
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: Tests the union function
****************************************************************************/
char test_2(FILE *output)
  {
  char     status = PASS;
  set_type set1,
	   set2,
	   result;
  unsigned i,
	   j[MAX_SET];

  /* initialize the sets */
  set1.start = NULL;
  set2.start = NULL;
  set1.comp_ele = comp_integers;
  set2.comp_ele = comp_integers;

  /* load set1 with even integers */
  for (i = 0; i < MAX_SET; i += 2)
    {
    j[i] = i;
    if (add(&set1, &j[i]) == FALSE)
      {
      fprintf(output,"\nERROR: Add not working, %d, elements:%ld\n",
	      i, set1.elements);
      status = FAIL;
      }
    }
  /* load set2 with odd integers */
  for (i = 1; i < MAX_SET; i += 2)
    {
    j[i] = i;
    if (add(&set2, &j[i]) == FALSE)
      {
      fprintf(output,"ERROR: Add not working, %d, elements:%ld\n",
	      i, set2.elements);
      status = FAIL;
      }
    }
  /* union of the two sets */
  if (set_union(&set1, &set2, &result) == FALSE)
    {
    fprintf(output,"ERROR: Union failed, size = %ld\n", result.elements);
    status = FAIL;
    }
  /* test the union for consecutive integers */
  for (i = 0; i < MAX_SET; i++)
    {
    if (is_an_element(&result, &i) == FALSE)
      {
      status = FAIL;
      fprintf(output,"ERROR: Element not found in RESULT set %d\n", i);
      }
    }
  /* delete the elements from all three sets */
  for (i = 0; i < MAX_SET; i += 1)
    {
    set_del_elem(&set1, &i);
    set_del_elem(&set2, &i);
    set_del_elem(&result, &i);
    }
  if ((set1.elements!=0L) || (set2.elements!=0L) || (result.elements!=0L))
    {
    status = FAIL;
    fprintf(output,"\nERROR: Sets not zero - set1:%ld  set2:%ld  result:%ld\n",
	    set1.elements, set2.elements, result.elements);
    }
  return(status);
  }


/****************************************************************************
   function: test_3
 parameters: none
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: Tests the intersection of two sets.  An intersection of
	     set A and set B is a set C where the elements in C are
	     found in both A and B.
****************************************************************************/
char test_3(FILE *output)
  {
  char     status = PASS;
  set_type set1,
	   set2,
	   result;
  unsigned i,
	   j[MAX_SET];

  set1.start = NULL;
  set2.start = NULL;
  set1.comp_ele = comp_integers;
  set2.comp_ele = comp_integers;

  /* intersection of the two empty sets should be empty */
  if (set_intersection(&set1, &set2, &result) == FALSE)
    {
    fprintf(output,"Intersection failed, size = %ld\n", result.elements);
    status = FAIL;
    }
  else
    {
    if (is_empty(&result) == FALSE)
      {
      fprintf(output,"ERROR: Empty sets intersection - RESULT NOT EMPTY\n");
      status = FAIL;
      }
    }
  /* load set1 with integers */
  for (i = 0; i < MAX_SET; i += 1)
    {
    j[i] =i;
    if (add(&set1, &j[i]) == FALSE)
      {
      fprintf(output,"ERROR: Add not working, %d, elements:%ld\n",
	      i, set1.elements);
      status = FAIL;
      }
    }
  /* load set2 with odd integers */
  for (i = 1; i < MAX_SET; i += 2)
    {
    j[i] = i;
    if (add(&set2, &j[i]) == FALSE)
      {
      fprintf(output,"ERROR: Add not working, %d, elements:%ld\n",
	      i, set2.elements);
      status = FAIL;
      }
    }
  /* intersection of the two sets should be odds */
  if (set_intersection(&set1, &set2, &result) == FALSE)
    {
    fprintf(output,"ERROR: Intersection failed, size = %ld\n",
	    result.elements);
    status = FAIL;
    }
  /* test for odds */
  for (i = 1; i < MAX_SET; i += 2)
    {
    if (is_an_element(&result, &i) == FALSE)
      {
      fprintf(output,"ERROR: element not found in RESULT set %d\n", i);
      status = FAIL;
      }
    }
  /* delete the elements from all three sets */
  for (i = 0; i < MAX_SET; i += 1)
    {
    set_del_elem(&set1, &i);
    set_del_elem(&set2, &i);
    set_del_elem(&result, &i);
    }
  if ((set1.elements!=0L) || (set2.elements!=0L) || (result.elements!=0L))
    {
    status = FAIL;
    fprintf(output,"ERROR: Sets not zero - set1:%ld  set2:%ld  result:%ld\n",
	    set1.elements, set2.elements, result.elements);
    }
  return(status);
  }


/****************************************************************************
   function: test_4
 parameters: none
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: Tests the symmetric difference of two sets.
****************************************************************************/
char test_4(FILE *output)
  {
  char     status = PASS;
  set_type set1,
	   set2,
	   result;
  unsigned i,
	   j[MAX_SET];

  set1.start = NULL;
  set2.start = NULL;
  set1.comp_ele = comp_integers;
  set2.comp_ele = comp_integers;

  /* load set1 with consecutive integers */
  for (i = 0; i < MAX_SET; i += 1)
    {
    j[i] = i;
    if (add(&set1, &j[i]) == FALSE)
      {
      fprintf(output,"ERROR: Add not working, %d, elements:%ld\n",
	      i, set1.elements);
      status = FAIL;
      }
    }
  /* load set2 with odd integers */
  for (i = 1; i < MAX_SET; i += 2)
    {
    j[i] = i;
    if (add(&set2, &j[i]) == FALSE)
      {
      fprintf(output,"ERROR: Add not working, %d, elements:%ld\n",
	      i, set2.elements);
      status = FAIL;
      }
    }
  /* symmetric_difference of the two sets will be even integers */
  if (set_symmetric_difference(&set1, &set2, &result) == FALSE)
    {
    fprintf(output,"ERROR: Symmetric difference failed, size = %ld\n",
	    result.elements);
    status = FAIL;
    }
  /* test for odd integers */
  for (i = 0; i < MAX_SET; i += 2)
    {
    if (is_an_element(&result, &i) == FALSE)
      fprintf(output,"ERROR: Element not found in RESULT set %d\n", i);
    }
  /* delete all elements from all three sets */
  for (i = 0; i < MAX_SET; i += 1)
    {
    set_del_elem(&set1, &i);
    set_del_elem(&set2, &i);
    set_del_elem(&result, &i);
    }
  if ((set1.elements!=0L) || (set2.elements!=0L) || (result.elements!=0L))
    {
    status = FAIL;
    fprintf(output,"ERROR: Sets not zero - set1:%ld  set2:%ld  result:%ld\n",
	    set1.elements, set2.elements, result.elements);
    }
  return(status);
  }


/****************************************************************************
   function: testout()

 parameters: passfail - boolean value (PASS or FAIL)
		  out - 5 character string

    returns: "PASS" is returned in the string (out) if passfail contains
	     a PASS char value.
	     "FAIL" is returned in the string (out) if passfail contains
	     a FAIL char value.

    purpose: This function converts a boolean PASS or FAIL value to a
	     string value "PASS" or "FAIL".
****************************************************************************/
char *testout(char passfail, char *out)
  {
  if (passfail == PASS)
    strcpy(out, "PASS");
  else
    strcpy(out, "FAIL");
  return(out);
  }

