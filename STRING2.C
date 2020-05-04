/* string2.C

   By Michael W. Maher
   1500 W. North St. Apt C15
   Jackson, MI 49202

   Ver 1.0 12/21/92

   DESCRIPTION: A set of C string manipulation routines designed to
		complement the Standard C library string manipulation
		routines found in <string.h>.

		17 of these functions were originally written by William
		Smith and first appeared in The C Users Journal - January
		1993 in his article "An Essential String Function Library."
		
		The Soundex function appeared in an article by Jeff Rosen
		in the The C Users Journal - September 1994 in his 
		article "A Simple Soundex Program."
		
		I have made many subsequent modifications to the functions.

   FUNCTIONS:   functions for finding or extracting a substring:

			str_nleft()
			str_nmid()
			str_nright()
			str_rstr()

		functions for editing strings:

			str_center()
			str_delete()
			str_insert()
			str_ljust()
			str_ltrim()
			str_mrplc()
			str_ocat()
			str_repeat()
			str_rev()
			str_rjust()
			str_rplc()
			str_rtrim()
			str_trim()
			str_vcat()

		soundex related functions
			soundex()

   PORTABILITY: ANSI Standard C
*/

/**************************** Include Files *******************************/
#include "string2.h"


/***************************************************************************
   function: str_nleft()

 parameters: string - string to get left characters
	     num    - number of characters to get

    returns: a string

    purpose: Get num leftmost characters in string.  Modifies string.
****************************************************************************/
char *str_nleft(char *string, size_t num)
  {
  if (num < strlen(string))
    string[num] = '\0';
  return(string);
  }                                    /* function str_nleft */


/***************************************************************************
   function: str_nmid()

 parameters: string - string to get substring in
	     pos    - index into string of start of midstr
	     num    - count of characters to get

    returns: a string

    purpose: Get num characters from the middle of a string.
	     Modifies string.
****************************************************************************/
char *str_nmid(char *string, size_t pos, size_t num)
  {
  char   *mid;
  size_t len = strlen(string);

  if (pos >= len)
    {
    /* if outside string */
    *string = '\0';
    return(string);
    }
  if (pos + num > len)
    num = len - pos;
  mid = &string[pos];
  memmove((void*)string, (void *) mid, num);
  string[num] = '\0';                  /* add end-of-string character */
  return(string);
  }                                    /* function str_nmid */


/***************************************************************************
   function: str_nright()

 parameters: string - string to get right characters
	     num    - number of characters to get

    returns: string

    purpose: Get num rightmost characters in string.  modifies string.
****************************************************************************/
char *str_nright(char *string, size_t num)
  {
  size_t len = strlen(string);

  return(str_nmid(string, (num > len ? 0 : len - num), min(num, len)));
  }                                    /* function str_nright */


/***************************************************************************
   function: str_nstr()

 parameters: string - string to search
	     find   - string to search for

    returns: A pointer to the last occurrence of substring find in
	     string or NULL if not found.

    purpose: Searches for last occurrence of sub string find within string.
****************************************************************************/
char *str_nstr(char *string, char *find)
  {
  char *str_result = NULL,
       *str_work   = string;

  while ((str_work = strstr(str_work, find)) != NULL)
    {
    str_result = str_work;
    str_work++;
    }
  return(str_result);
  }                                    /* function str_rstr */



/***************************************************************************
   function: str_center()

 parameters: string - string to center
	     len    - number of characters of centered string

    returns: string

    purpose: Centers a string in a desired length by removing tabs and
	     adding spaces to both sides of the string.
****************************************************************************/
char *str_center(char *string, size_t len)
  {
  size_t lenorg;

  /* trim spaces and tabs off the string */
  str_trim(string, " \t");
  lenorg = strlen(string);
  if (len > lenorg)
    {
    /* since desired string length is longer than the original add the
       spaces to each side */
    str_rjust(string, (lenorg + len) / 2);
    str_ljust(string, len);
    }
  return(string);
  }                                    /* function str_center */


/***************************************************************************
   function: str_delete()

 parameters: string - string to edit
	     pos    - index to start deleting characters
	     num    - number of characters to delete

    returns: string

    purpose: Modifies string, by deleting num characters beginning at pos.
****************************************************************************/
char *str_delete(char *string, char *pos, size_t num)
  {
  size_t len = strlen(string);

  if((pos < &string[len]) && (num > 0))
    {
    /* inside string and characters to delete */
    num = min(num, strlen(pos));
    if (num)
      {
      /* delete characters by concatenating */
      memmove(pos, &pos[num], strlen(&pos[num]) + 1);
      }
    }
  return(string);
  }                                    /* function str_delete */


/***************************************************************************
   function: str_insert()

 parameters: string - string to edit
	     pos    - pointer to location within string
	     insrt  - string to insert into string

    returns: string

    purpose: Inserts a string insrt into string at pos.
****************************************************************************/
char *str_insert(char *string, char *pos, char *insrt)
  {
  size_t len  = strlen(insrt);
  char   *tmp = &pos[len];

  memmove(tmp, pos, strlen(pos) + 1);  /* make room in middle of string */
  memmove(pos, insrt, len);            /* move insrt into middle of string */
  return(string);
  }                                    /* function str_insert */


/***************************************************************************
   function: str_ljust()

 parameters: string - string to left justify
	     len    - length of string

    returns: string

    purpose: Pads right end of string with spaces to left justify string
	     to a new length len.
****************************************************************************/
char *str_ljust(char *string, size_t len)
  {
  size_t lenorg = strlen(string);
  char   *strend = &string[lenorg];

  len = max(len, lenorg) - lenorg;
  strend[len] = '\0';
  while (len)
    {
    len--;
    strend[len] = ' ';
    }
  return(string);
  }                                    /* function str_ljust */


/***************************************************************************
   function: str_ltrim()

 parameters: string - string to trim
	     trim - string containing chars to trim

    returns: string

    purpose: Delete characters from the left end of string that are
	     contained in trim.
****************************************************************************/
char *str_ltrim(char *string, char *trim)
  {
  size_t num = strspn(string, trim);

  str_delete(string, string, num);
  return(string);
  }                                    /* function str_ltrim */


/***************************************************************************
   function: str_mrplc()

 parameters: string - string to edit
	     find   - search string
	     rplc   - replacement string

    returns: string

    purpose: Find and replace all occurances of find within string with rplc.
****************************************************************************/
char *str_mrplc(char *string, char *find, char *rplc)
  {
  char *strwork = string;
  size_t lenrplc = strlen(rplc);

  while ((strwork = strstr(strwork, find)) != NULL)
    {
    str_delete(string, strwork, strlen(find));
    str_insert(string, strwork, rplc);
    strwork += lenrplc;
    }
  return(string);
  }                                    /* function str_mrplc */


/***************************************************************************
   function: str_ocat()

 parameters: dest   - destination string
	     string - string to concatenate

    returns: dest

    purpose: Concatenate overlapped strings.  This function behaves in the
	     same fashion as strcat() in <string.h>.  This version will
	     work for strings that overlap in memory.

       note: This function was originaly published by William Smith (the
	     author).  Smith's version would not return the destination
	     string but the string to concatenate. The following is my
	     version of the fuction and it is correct.
****************************************************************************/
char *str_ocat(char *dest, char *string)
  {
  memmove((void *) &dest[strlen(dest)], (void*) string, strlen(string) + 1);
  return(dest);
  }                                    /* function str_ocat */


/***************************************************************************
   function: str_repeat()

 parameters: string - string buffer to load
	     rpt    - repetition string
	     num    - number of repetitions

    returns: string

    purpose: Builds a string of (num * strlen(rpt)) by repeating a
	     substring rpt.

       note: This function was originaly published by William Smith (the
	     author).  Smith's version would fail with a divide by zero
	     error when given a repetition string of NULL values.  It did
	     not function as described above. The following is my version
	     of the fuction and it with work for null string cases and
	     functions as described above.
****************************************************************************/
char *str_repeat(char *string, char *rpt, size_t num)
  {
  size_t i;

  if (num > 0)
    strcpy(string, rpt);               /* build 1st repitition */
  for (i = 1; i < num; i++)
     strcat(string, rpt);              /* add remaining repititions */
  return(string);
  }                                    /* function str_repeat */


/***************************************************************************
   function: str_rev()

 parameters: string - string reverse

    returns: a string

    purpose: Reverses the order of characters in string.
****************************************************************************/
char *str_rev(char *string)
  {
  char *beg = string,
       *end = &string[strlen(string) - 1],
       temp;
       
  while (beg < end)
    {
    temp = *end;
    *end = *beg;
    *beg = temp;
    beg++;
    end--;
    }
  return(string);
  }                                    /* function str_rev */


/***************************************************************************
   function: str_rplc()

 parameters: string - string to edit
	     find   - search string
	     rplc   - replacement string

    returns: string

    purpose: String search and replace function.  This function will
	     replace the first occurrences of find within string with rplc.
****************************************************************************/
char *str_rplc(char *string, char *find, char *rplc)
  {
  char *strwork = strstr(string, find);

  if (strwork)
    {
    str_delete(string, strwork, strlen(find));
    str_insert(string, strwork, rplc);
    }
  return(string);
  }                                    /* function str_rplc */


/***************************************************************************
   function: str_rjust()

 parameters: string - string to edit
	     len    - new length of string

    returns: string

    purpose: Pads the left end of string so that it is right justified to
	     a total length of len.
****************************************************************************/
char *str_rjust(char *string, size_t len)
  {
  size_t lenorg = strlen(string);

  len = max(lenorg, len) - lenorg;
  if (len)
    {
    memmove(&string[len], string, lenorg + 1);
    while (len)
      {
      len--;
      string[len] = ' ';
      }
    }
  return(string);
  }                                    /* function str_rjust */


/***************************************************************************
   function: str_rtrim()

 parameters: string - string to trim
	     trim   - string of characters to trim

    returns: string

    purpose: Delete characters from the rights end of string that are
	     contained in trim.
****************************************************************************/
char *str_rtrim(char *string, char *trim)
  {
  char *strwork = &string[strlen(string) - 1];

  /* look for last character in string no being in trim string */
  while ((string != strwork) && (strspn(strwork, trim) != 0))
    {
    *strwork-- = '\0';
    }
  return(string);
  }                                    /* function str_rtrim */


/***************************************************************************
   function: str_trim()

 parameters: string - string to trim
	     trim   - string of characters to trim

    returns: string

    purpose: Delete characters from both ends of string.
****************************************************************************/
char *str_trim(char *string, char *trim)
  {
  str_ltrim(string, trim);
  str_rtrim(string, trim);
  return(string);
  }                                    /* function str_trim */


/***************************************************************************
   function: str_vcat()

 parameters: dest - destination string
	     str1 - required first string

    returns: dest

    purpose: A variable argument version of strcat().  Concatenates a list
	     of strings into a destination string.  The last argument must
	     be a NULL pointer.

       note: This function was originaly published by William Smith (the
	     author).  Smith's version would fail to run as described
	     above (even the most basic test).

	     The following is my version of the fuction and it works for
	     all cases including overlapping strings.
****************************************************************************/
char *str_vcat(char *dest, char *str1,...)
  {
  va_list vararglist;
  char    *string;

  str_ocat(dest, str1);
  va_start(vararglist, dest);          /* initialize variable arguements */
  while ((string = va_arg(vararglist, char*))!= NULL)
    str_ocat(dest, string);            /* loop through all the arguments */
  va_end(vararglist);                  /* clean up */
  return(dest);
  }                                    /* function str_vcat */


/***************************************************************************
   function: soundex()

 parameters: in_name
	     code

    returns: 0

    purpose: This function will assign a soundex code for a given 
             string.

       note: Soundex is a useful search tool for names having a known 
             sound, but unknown spelling.  Also, Soundex can sometimes
             resolve minor differences in the spelling of names when 
             searching for duplicates.  Because the algorithm is 
             simple, it's easy to fine tune it to a specific application.
             
             Letters		Numeric Code
             _________________	_____________
             A,E,I,H,O,U,W,Y	IGNORED
             B,F,P,V		1
             C,G,J,K,Q,S,X,Z	2
             D,T		3
             L			4
             M,N		5
             R			6
****************************************************************************/
int soundex(char *in_name, char *code)
  {
  /* ctable contains the soundex value of each letter in alphabetical 
     order.  0 represents letters which are to be ignored */
  static char ctable[] = {"01230120022455012623010202"};   
  char name[MAX_LENGTH + 1],
       prior = ' ', 
       c;
  short i,
        y=0;
  
  /* convert name to all upper case */
  for (i=0; in_name[i] && i < MAX_LENGTH; i++)
    name[i] = toupper(in_name[i]);
  name[i] = '\0';
  /* generate 1st character of Soundex code */
  code[0] = name[0];
  y=1;
  code[y] = '\0';
  
  #ifdef MODIFIED_SOUNDEX_ENGLISH
  if (name[0] == 'K')
    code[0] = 'C';
  else if (name[0] == 'P' && name[1] == 'H')
    code[0] = 'F';
  #endif
  
  /* loop through rest of name, until code complete */
  for (i=1; name[i]; i++)
    {
    /* skip non alpha */
    if (! isalpha(name[i]))		
      continue;
      
    /* skip successive occurance */
    if (name[i] == prior)
      continue;
    prior = name[i];
    
    /* lookup letter in table */
    c = name[i] - ALPHA_OFFSET;
    
    /* ignore this letter */
    if (ctable[c] == '0') 
      continue;
    
    /* add to code */
    code[y++] = ctable[c];
    code[y] = '\0';
    
    /* check to see if code is complete */
    if (strlen(code) >= SOUNDEX_LENGTH)
      break;
      
    }
  while (strlen(code) < SOUNDEX_LENGTH)
    {
    code[y++] = '0';
    code[y]   = '\0';
    }  
  return(0);
  }
/* end of file */
