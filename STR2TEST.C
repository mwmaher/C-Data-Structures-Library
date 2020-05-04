/* str2test.c

   By Michael W. Maher

   Ver 1.0 12/21/92
   Ver 1.5 09/19/94

   DESCRIPTION: The following is a test program for the <string2.h>
		library of functions. It is designed to test a set of
		C string manipulation routines used to complement the
		Standard C library string manipulation routines found
		in <string.h>.

		17 of the functions tested were originally written by
		William Smith and first appeared in The C Users Journal
		- January 1993 in his article "An Essential String
		Function Library."

		Of these, 3 were found to have serious errors and were
		rewritten by myself.  These new functions are now my
		original work:


   PORTABILITY: ANSI Standard C
*/

/**************************** Include Files ********************************/
#include <stdio.h>
#include "string2.h"
#include "string2.c"

/************************** Constants & Macros *****************************/
#define PASS 0
#define FAIL 1

/*************************** Data Structures *******************************/


/************************** function prototypes ****************************/
int  main(int argc, char **argv);
char test1(FILE *output);
char test2(FILE *output);
char test3(FILE *output);
char test4(FILE *output);
char test5(FILE *output);
char test6(FILE *output);
char test7(FILE *output);
char test8(FILE *output);
char test9(FILE *output);
char test10(FILE *output);
char test11(FILE *output);
char test12(FILE *output);
char test13(FILE *output);
char test14(FILE *output);
char test15(FILE *output);
char test16(FILE *output);
char test17(FILE *output);
char test18(FILE *output);
char test19(FILE *output);

char *testout(char passfail, char *out);


int main(int argc, char **argv)
  {
  FILE *output = stdout;
  char buf[81];
  int  i = 1;

  fprintf(stdout, "\n"
		  "str2test.c By Michael W. Maher\n"
		  "Ver 1.0: 12/22/92\n"
		  "This program will test the functions found in "
		  "string2.h\n");
  if ((argc > 2) || ((argc == 2) && (strncmp(argv[1], "/H", 2) == 0)))
    {
    fprintf(stdout, "\nParameters: [resultfile]|[/H]\n");
    return(0);
    }
  else if ((argc == 2) && ((output = fopen(argv[1], "rt")) != NULL))
    {
    fprintf(output, "ERROR: [%s] already exists.\n", argv[1]);
    return(0);
    }
  else if ((argc == 2) && ((output = fopen(argv[1], "wt")) == NULL))
    {
    fprintf(output, "ERROR: Unable to create [%s].\n", argv[1]);
    return(-1);
    }
  fprintf(output, "TEST #%d: %s\n", i++, testout(test1(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test2(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test3(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test4(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test5(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test6(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test7(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test8(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test9(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test10(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test11(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test12(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test13(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test14(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test15(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test16(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test17(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test18(output), buf));
  fprintf(output, "TEST #%d: %s\n", i++, testout(test19(output), buf));
  return(0);
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


/***************************************************************************
   function: test1()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_nleft() function.
****************************************************************************/
char test1(FILE *output)
  {
  char test = PASS,
       *string = "This is a test string";

  if (strcmp(str_nleft(string, 30), "This is a test string") != 0)
    {
    fprintf(output, "Num larger than string length [%s].\n", string);
    test = FAIL;
    }
  else if (strcmp(str_nleft(string, 21), "This is a test string") != 0)
    test = FAIL;
  else if (strcmp(str_nleft(string, 25), "This is a test string") != 0)
    test = FAIL;
  else if (strcmp(str_nleft(string, 14), "This is a test") != 0)
    test = FAIL;
  else if (strcmp(str_nleft(string, 4), "This") != 0)
    test = FAIL;
  else if (strcmp(str_nleft(string, 1), "T") != 0)
    test = FAIL;
  else if (strcmp(str_nleft(string, 0), "") != 0)
    test = FAIL;
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string);
  return(test);
  }


/***************************************************************************
   function: test2()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_nmid() function.
****************************************************************************/
char test2(FILE *output)
  {
  char test = PASS,
       *string = "This is a test string";

  if (strcmp(str_nmid(string, 0, 30), "This is a test string") != 0)
    test = FAIL;
  else if (strcmp(str_nmid(string, 0, 21), "This is a test string") != 0)
    test = FAIL;
  else if (strcmp(str_nmid(string, 1, 19), "his is a test strin") != 0)
    test = FAIL;
  else if (strcmp(str_nmid(string, 9, 10), "test strin") != 0)
    test = FAIL;
  else if (strcmp(str_nmid(string, 9, 1), "n") != 0)
    test = FAIL;
  else if (strcmp(str_nmid(string, 0, 0), "") != 0)
    test = FAIL;
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string);
  return(test);
  }


/***************************************************************************
   function: test3()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_nright() function.
****************************************************************************/
char test3(FILE *output)
  {
  char test = PASS,
       *string = "This is a test string";

  if (strcmp(str_nright(string, 30), "This is a test string") != 0)
    test = FAIL;
  else if (strcmp(str_nright(string, 21), "This is a test string") != 0)
    test = FAIL;
  else if (strcmp(str_nright(string, 19), "is is a test string") != 0)
    test = FAIL;
  else if (strcmp(str_nright(string, 6), "string") != 0)
    test = FAIL;
  else if (strcmp(str_nright(string, 1), "g") != 0)
    test = FAIL;
  else if (strcmp(str_nright(string, 0), "") != 0)
    test = FAIL;
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string);
  return(test);
  }


/***************************************************************************
   function: test4()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_nstr() function.
****************************************************************************/
char test4(FILE *output)
  {
  char test    = PASS,
       *string = "This is a best test sing ring string";

  if (strcmp(str_nstr(string, "ing"), "ing") != 0)
    {
    fprintf(output, "[%s]\n", str_nstr(string, "ing"));
    test = FAIL;
    }
  else if (strcmp(str_nstr(string, "ring"), "ring") != 0)
    {
    fprintf(output, "[%s]\n", str_nstr(string, "ring"));
    test = FAIL;
    }
  else if (strcmp(str_nstr(string, "est"), "est sing ring string") != 0)
    {
    fprintf(output, "[%s]\n", str_nstr(string, "est"));
    test = FAIL;
    }
  else if (strcmp(str_nstr(string, "g"), "g") != 0)
    {
    fprintf(output, "[%s]\n", str_nstr(string, "g"));
    test = FAIL;
    }
  else if (strcmp(str_nstr(string, "T"),
		  "This is a best test sing ring string") != 0)
    {
    fprintf(output, "[%s]\n", str_nstr(string, "T"));
    test = FAIL;
    }
  
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string);
  return(test);
  }


/***************************************************************************
   function: test5()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_center() function.
****************************************************************************/
char test5(FILE *output)
  {
  char test     = PASS,
       string[80],
       string2[80];

  strcpy(string, "my string");
  strcpy(string2, string);
  if (strcmp(str_center(string, strlen(string)), "my string") != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_center(string, (strlen(string) + 2)),
		  " my string ") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_center(string, strlen(string) + 3),
		  "  my string   ") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_center(string, strlen(string) + 4),
		  "    my string     ") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_center(string, strlen(string) - 10),
		  "my string") != 0)
    {
    fprintf(output, "5 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_center(string, (size_t) 0),
		  "my string") != 0)
    {
    fprintf(output, "6 [%s]\n", string);
    test = FAIL;
    }
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string2);
  return(test);
  }


/***************************************************************************
   function: test6()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_delete() function.
****************************************************************************/
char test6(FILE *output)
  {
  char test     = PASS,
       string[80],
       string2[80];

  strcpy(string, "This is my test string.");
  strcpy(string2, string);
  if (strcmp(str_delete(string, &string[0], 0),
	     "This is my test string.") != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_delete(string, &string[strlen(string) - 1], 1),
		  "This is my test string") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_delete(string, &string[strlen(string) - 3], 3),
		  "This is my test str") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_delete(string, &string[1], 1),
		  "Tis is my test str") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_delete(string, &string[5], 5),
		  "Tis itest str") != 0)
    {
    fprintf(output, "5 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_delete(string, &string[0], 1),
		  "is itest str") != 0)
    {
    fprintf(output, "6 [%s]\n", string);
    test = FAIL;
    }
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string2);
  return(test);
  }


/***************************************************************************
   function: test7()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_insert() function.
****************************************************************************/
char test7(FILE *output)
  {
  char test     = PASS,
       string[80],
       string2[80];

  strcpy(string, "This is my test string.");
  strcpy(string2, string);
  if (strcmp(str_insert(string, &string[strlen(string)], "  So?"),
	     "This is my test string.  So?") != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_insert(string, &string[strlen(string)], "  Ha!"),
		  "This is my test string.  So?  Ha!") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_insert(string, &string[strlen(string) - 6], " what"),
		  "This is my test string.  So what?  Ha!") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_insert(string, string, "Ha!  "),
		  "Ha!  This is my test string.  So what?  Ha!") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string2);
  return(test);
  }


/***************************************************************************
   function: test8()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_ljust() function.
****************************************************************************/
char test8(FILE *output)
  {
  char test = PASS,
       string[80],
       string2[80];

  strcpy(string, "This is my test string.");
  strcpy(string2, string);
  if (strcmp(str_ljust(string, strlen(string)),
	     "This is my test string.") != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_ljust(string, strlen(string) + 1),
		  "This is my test string. ") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_ljust(string, strlen(string) + 4),
		  "This is my test string.     ") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_ljust(string, 5),
		  "This is my test string.     ") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string2);
  return(test);
  }

/***************************************************************************
   function: test9()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_ltrim() function.
****************************************************************************/
char test9(FILE *output)
  {
  char test = PASS,
       string[80],
       string2[80];

  strcpy(string, "This wish is my test stringish.");
  strcpy(string2, string);
  if (strcmp(str_ltrim(string, "This "), "wish is my test stringish.") != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_ltrim(string, "is"), "wish is my test stringish.") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_ltrim(string, "."), "wish is my test stringish.") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_ltrim(string, "w"), "ish is my test stringish.") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_ltrim(string, "ish is my test stringish."), "") != 0)
    {
    fprintf(output, "5 [%s]\n", string);
    test = FAIL;
    }
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string2);
  return(test);
  }


/***************************************************************************
   function: test10()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_mrplc() function.
****************************************************************************/
char test10(FILE *output)
  {
  char test = PASS,
       string[80],
       string2[80];

  strcpy(string, "This wish is my test stringish.");
  strcpy(string2, string);
  if (strcmp(str_mrplc(string, "z", "x"),
	     "This wish is my test stringish.") != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_mrplc(string, "T", "t"),
		  "this wish is my test stringish.") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test  = FAIL;
    }
  else if (strcmp(str_mrplc(string, "is", "si"),
		  "thsi wsih si my test stringsih.") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string2);
  return(test);
  }


/***************************************************************************
   function: test11()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_ocat() function.
****************************************************************************/
char test11(FILE *output)
  {
  char test = PASS,
       string[80],
       string2[80];

  strcpy(string, "my test string.");
  strcpy(string2, string);
   if (strcmp(str_ocat(string, "."), "my test string..") != 0)
    {
    strcpy(string, string2);
    fprintf(output, "1 before [%s]  after [%s] new length=%d\n",
	    string,
	    str_ocat(string, "."),
	    strlen(string));
    test = FAIL;
    }
  else if (strcmp(str_ocat(string, &string[strlen(string) - 1]),
		  "my test string...") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_ocat(string, string),
		  "my test string...my test string...") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_ocat(string, &string[strlen(string) - 2]),
		  "my test string...my test string.....") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  if (test == FAIL)
    fprintf(output, "string = [%s]\n", string2);
  return(test);
  }


/***************************************************************************
   function: test12()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_repeat() function.
****************************************************************************/
char test12(FILE *output)
  {
  char test = PASS,
       string[80],
       null_string[80];

  memset(null_string, '\0', 80);
  if (strcmp(str_repeat(string, ".", 5), ".....") != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_repeat(string, "..", 1), "..") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_repeat(string, "Big ", 2), "Big Big ") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_repeat(string, "!", 0), "Big Big ") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  return(test);
  }


/***************************************************************************
   function: test13()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_rplc() function.
****************************************************************************/
char test13(FILE *output)
  {
  char test = PASS,
       string[80],
       null_string[80];

  strcpy(string, "This his is business lisp.");
  memset(null_string, '\0', 80);
  if (strcmp(str_rplc(string, null_string, ""), string) != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rplc(string, ".", "!"),
			   "This his is business lisp!") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rplc(string, "This his is b", "B"),
			   "Business lisp!") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rplc(string, "iness ", " "), "Bus lisp!") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rplc(string, "s", ""), "Bu lisp!") != 0)
    {
    fprintf(output, "5 [%s]\n", string);
    test = FAIL;
    }
  return(test);
  }


/***************************************************************************
   function: test14()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_rjust() function.
****************************************************************************/
char test14(FILE *output)
  {
  char test = PASS,
       string[80],
       null_string[80];

  strcpy(string, "This his is business lisp.");
  memset(null_string, '\0', 80);
  if (strcmp(str_rjust(string, 0), string) != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rjust(null_string, 0), null_string) != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rjust(null_string, 2),
			   "  ") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rjust(string, strlen(string) + 2),
		 "  This his is business lisp.") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rjust(string, 1),
		  "  This his is business lisp.") != 0)
    {
    fprintf(output, "5 [%s]\n", string);
    test = FAIL;
    }
  return(test);
  }


/***************************************************************************
   function: test15()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_rtrim() function.
****************************************************************************/
char test15(FILE *output)
  {
  char test = PASS,
       string[80],
       string2[80];

  strcpy(string, "This wish is my test stringish.");
  strcpy(string2, string);
  if (strcmp(str_rtrim(string, "This "), string) != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rtrim(string, "is"), string) != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rtrim(string, "."),
		  "This wish is my test stringish") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rtrim(string, "ish"),
		  "This wish is my test string") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_rtrim(string, ""), string) != 0)
    {
    fprintf(output, "5 [%s]\n", string);
    test = FAIL;
    }
  return(test);
  }


/***************************************************************************
   function: test16()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_trim() function.
****************************************************************************/
char test16(FILE *output)
  {
  char test = PASS,
       string[80];

  strcpy(string, "I wish my sigh would buy my wish I.");
  if (strcmp(str_trim(string, ""),
	     "I wish my sigh would buy my wish I.") != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_trim(string, "wish"),
		  "I wish my sigh would buy my wish I.") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_trim(string, "."),
		  "I wish my sigh would buy my wish I") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_trim(string, "I"),
		  " wish my sigh would buy my wish ") != 0)
    {
    fprintf(output, "4 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_trim(string, " wish "),
		  "my sigh would buy my") != 0)
    {
    fprintf(output, "5 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_trim(string, "ymub "),
		  "sigh would") != 0)
    {
    fprintf(output, "5 [%s]\n", string);
    test = FAIL;
    }
  return(test);
  }


/***************************************************************************
   function: test17()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_vcat() function.
****************************************************************************/
char test17(FILE *output)
  {
  char test = PASS,
       string[80];

  memset(string, '\0', 80);
  strcpy(string, "This");
  if (strcmp(str_vcat(string, " is", " only", NULL),
		  "This is only") != 0)
    {
    fprintf(output, "1 [%s]\n", string);
    test = FAIL;
    }
  else if (strcmp(str_vcat(string, " a", " test", ".", NULL),
		  "This is only a test.") != 0)
    {
    fprintf(output, "2 [%s]\n", string);
    test = FAIL;
    }
  /* test case of overlapping strings */
  else if (strcmp(str_vcat(string, " ", string, NULL),
		  "This is only a test. This is only a test. ") != 0)
    {
    fprintf(output, "3 [%s]\n", string);
    test = FAIL;
    }
  return(test);
  }



/***************************************************************************
   function: test18()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the str_rev() function.
****************************************************************************/
char test18(FILE *output)
  {
  char test = PASS;
  char string[80];
  
  /* even number of letters */
  strcpy(string, "This");
  if (strcmp(str_rev(string), "sihT") != 0)
    {
    strcpy(string, "This");
    fprintf(output, "ERROR: test 18 - reversing [%s] produced [%s]\n",
	    "This", str_rev(string));
    test = FAIL;
    }
  /* odd number of letters */
  strcpy(string, "12345");  
  if (strcmp(str_rev(string), "54321") != 0)
    {
    strcpy(string, "12345");
    fprintf(output, "ERROR: test 18 - reversing [%s] produced [%s]\n",
	    "12345", str_rev(string));
    test = FAIL;
    }
  /* one letter */
  strcpy(string, "O");  
  if (strcmp(str_rev(string), "O") != 0)
    {
    strcpy(string, "O");
    fprintf(output, "ERROR: test 18 - reversing [%s] produced [%s]\n",
	    "O", str_rev(string));
    test = FAIL;
    }
  return(test);
  }
  
  
/***************************************************************************
   function: test19()

 parameters: output - stream to write test results to

    returns: PASS or FAIL

    purpose: To test the soundex() function.
****************************************************************************/
char test19(FILE *output)
  {
  char test = PASS;
  char string[80],
       soundexcode[SOUNDEX_LENGTH];
  
  strcpy(string, "Jones");
  soundex(string, soundexcode);
  if (!strcmp(soundexcode, 'J520'))
    {
    fprintf(output,"ERROR: test 19 - %s != %s", string, soundexcode);
    test = FAIL;
    }
  
  strcpy(string, "Mosbacher");
  soundex(string, soundexcode);
  if (!strcmp(soundexcode, 'M212'))
    {
    fprintf(output,"ERROR: test 19 - %s != %s", string, soundexcode);
    test = FAIL;
    }

  strcpy(string, "Agganis");
  soundex(string, soundexcode);
  if (!strcmp(soundexcode, 'A252'))
    {
    fprintf(output,"ERROR: test 19 - %s != %s", string, soundexcode);
    test = FAIL;
    }

  return(test);
  }
