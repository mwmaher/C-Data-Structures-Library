/* string2.H

   By Michael W. Maher

   Ver 1.0 12/21/92

   DESCRIPTION: Include file for String2.C
		String manipulation routines.

   PORTABILITY: ANSI Standard C
*/
/* min and max macros */
#ifndef max
  #define max(a,b)    (((a) > (b)) ? (a) : (b))
  #define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif


#ifndef MSTRINGH
  #define MSTRINGH

  /**************************** Include Files ******************************/
  #include <ctype.h>			/* standard c */
  #include <stdarg.h>                  	/* standard c */
  #include <stdio.h>		       	/* standard c */	
  #include <stdlib.h>                  	/* standard c */
  #include <string.h>                  	/* standard c */

  /************************** function prototypes **************************/
  /* functions for extracting or finding a substring */

  /* get num leftmost characters in string */
  char *str_nleft(char *string, size_t num);

  /* get num characters from middle of string */
  char *str_nmid(char *string, size_t pos, size_t num);

  /* get num rightmost characters in string */
  char *str_nright(char *string, size_t num);

  /* searches for last occurrence of substring find within string */
  char *str_nstr(char *str, char *find);


  /* functions for editing strings */

  /* Centers a string in desired length by removing tabs and adding spaces */
  char *str_center(char *string, size_t len);

  /* Delete num characters beginning at pos in string */
  char *str_delete(char *string, char *pos, size_t num);

  /* Insert insrt into string at pos */
  char *str_insert(char *string, char *pos, char *insrt);

  /* Pad right end of string with spaces to left justify string to length */
  char *str_ljust(char *string, size_t len);

  /* Delete characters from the left end of string that are contain in trim */
  char *str_ltrim(char *string, char *trim);

  /* Multiple search and replace all occurances of find in string with rplc */
  char *str_mrplc(char *string, char *find, char *rplc);

  /* Behaves the same as strcat() but will work with overlapping strings */
  char *str_ocat(char *dest, char *string);

  /* Builds a string of length num, by repeating a substring rpt */
  char *str_repeat(char *string, char *rpt, size_t num);

  /* Reverse the order of the characters in string. */
  char *str_rev(char *string);

  /* Search and replace first occurrence of find within str with rplc */
  char *str_rplc(char *string, char *find, char *rplc);

  /* Pad the left end of string so that it is right justified to length */
  char *str_rjust(char *string, size_t len);

  /* Delete characters from the right end of string that are in trim */
  char *str_rtrim(char *string, char *trim);

  /* Delete characters from both ends of str */
  char *str_trim(char *string, char *trim);

  /* Variable argument version of strcat(), conccatinates list of strings */
  char *str_vcat(char *dest, char *str1,...);


  /* Soundex related functions */
  #define ALPHA_OFFSET 65
  #define SOUNDEX_LENGTH 4
  #define MAX_LENGTH 20
  int soundex(char *in_name, char *code);

#endif
/* end of include listing */
