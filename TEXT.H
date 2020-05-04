/* Text.H

   By Michael W. Maher

   Ver 1.0 10/7/92

   The following header provides functions for string matching and
   searching routines.

   DESCRIPTION:
      The string matching problem consists of finding all occurances of a
      pattern of length m in a text of length n.

      Variations of the problem include finding solutions with or without
      a x number of mismatching errors.

      The worst-case time complexity for small pattern strings is linear
      with respect to the size of the text.

   OPERATORS:
      str_match_so()    Shift-Or algorithm for string matching
      str_search_sa()   string matching with mismatching allowed
*/

/*************************** defined constants *****************************/
#define MATCH 1
#define MISMATCH 0
#define MAXSYM 128                     /* size of the alphabet (ASCII) */
#define B 1                            /* number of bits per state */
#define EOS NULL                       /* end of string */
#define WORD 16                        /* word size in bits */

/***************************** header files ********************************/
#include <stdio.h>
#include <string.h>

/************************** function prototypes ****************************/
/* Shift-Or algorithm for string matching */
unsigned str_match_so(char *text, char *pattern);

/* Shift-Add algorithm for string matching with at most k mismatches */
unsigned str_match_sa(register char *text, char *pattern, int k);

/* The ceiling function of log2(x) */
int clog2(int x);
