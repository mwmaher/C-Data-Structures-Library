/* TextTest.C

   By Michael W. Maher
   1500 W. North St. Apt C15
   Jackson, MI 49202

   Ver 1.0 10/7/92

   The following functions provide testing of string matching and
   searching routines found in TEXT.C.

   DESCRIPTION:
      The string matching problem consists of finding all occurances of a
      pattern of length m in a text of length n.

      Variations of the problem include finding solutions with or without
      a x number of mismatching errors.

      The worst-case time complexity for small pattern strings is linear
      with respect to the size of the text.

   OPERATORS:
      str_match_so()    Shift-Or algorithm for string matching k
      str_search_sa()   Shift-Add algorithm for str match with mismatching
*/

/***************************** header files ********************************/
#include <stdio.h>
#include <string.h>
#include "toolkit.h"
#include "text.h"

/***************************** source code *********************************/
#include "text.c"

/**************************** function prototypes *************************/
void main(void);
char test1(FILE *output);
char test2(FILE *output);
char *testout(char passfail, char *out);

/*************************** main body of program *************************/
void main(void)
  {
  FILE *output;
  char buf[81];

  output = stdout;
  fprintf(output, "TEST #%d: %s\n", 1, testout(test1(output), buf));
  fprintf(output, "TEST #%d: %s\n", 2, testout(test2(output), buf));
  return;
  }


/****************************************************************************
   function: test1()

 parameters: output - file ptr to output source

    returns: PASS - if successful
	     FAIL - if no successful

    purpose: This function performs a simple test of the string matching
	     function based on the Shift-Or algorithm - str_match_so().
	     It passes in a simple string and a simple pattern for the
	     function to evaluate.
****************************************************************************/
char test1(FILE *output)
  {
  #define ACTUAL_MATCHES 3
  unsigned num_found;
  register char *text,
		*pat;

  text = "This is my testy text test string for the terrible test.";
  pat  = "test";
  num_found = str_match_so(text, pat); /* the function being tested */
  if (num_found == ACTUAL_MATCHES)
    return(PASS);
  else
    {
    /* did not work print a message and return FAIL */
    fprintf(output, "\nERROR:\n"
	 " TEXT = %s\n"
	 " PATTERN = %s\n"
	 " PATTERNS FOUND = %u\n\n", text, pat, num_found);
    return(FAIL);
    }
  }


/****************************************************************************
   function: test2()

 parameters: output - file ptr to output source

    returns: PASS - if successful
	     FAIL - if no successful

    purpose: This function performs a simple test of the string matching
	     function based on the Shift-Or algorithm - str_match_sa().
	     This particular implementation allows for mismatching.  This
	     test will use mismatching at k = 0, k = 1, and k = 2;
****************************************************************************/
char test2(FILE *output)
  {
  #define MAX_MISMATCH 4
  unsigned num_found[MAX_MISMATCH],
	   actual_matches[MAX_MISMATCH],
	   k;
  register char *text,
		*pat,
		test = PASS;

  actual_matches[0] = 1;
  actual_matches[1] = 4;
  actual_matches[2] = 5;
  actual_matches[3] = 10;
  /*at k=0                                                1          */
  /*at k=1    1                     2                     3    4     */
  /*at k=2    1                2    3                     4    5     */
  /*at k=3    1         2    3  4    5      6 7       8   9    10    */
  text = "Mr. mat never took a late bath, but he knew his math myths.";
  pat  = "math";
  /* find the number of occurances of pat in text with a most k mismatches */
  for (k = 0; k < MAX_MISMATCH; k++)
    {
    num_found[k] = str_match_sa(text, pat, k); /* the function being tested */
    if (num_found[k] != actual_matches[k])
      test = FAIL;
    }
  if (test == FAIL)
    {
    /* did not work print a message and return FAIL */
    fprintf(output, "\nERROR:\n"
	 " TEXT = %s\n"
	 " PATTERN = %s\n", text, pat);
    for (k = 0; k < MAX_MISMATCH; k++)
      fprintf(output, " %u ", num_found[k]);
    fprintf(output, "\n");
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

