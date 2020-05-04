/* Text.C

   By Michael W. Maher
   1500 W. North St. Apt C15
   Jackson, MI 49202

   Ver 1.0 10/7/92

   The following functions provide string matching and searching routines.

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

/***************************************************************************
   function:str_match_so()

 parameters:    text - text to be searched
	     pattern - string pattern to be searched for

    returns: The number of occurances of (pattern) in (text).

    purpose: Use to determine the number of occurances of a pattern in a
	     given string.  The string matching code is a representation
	     of the Shift-Or algorithm presented by Baeza-Yates and Gonnet
	     in "A New Approach to Text Searching", Communications Of The
	     ACM (October 1992).  One serious error has been eliminated and
	     several other minor errors and sylistic changes have been made
	     by Michael W. Maher.
****************************************************************************/
unsigned str_match_so(register char *text, char *pattern)
  {
  register char     first = *pattern;           /* 1st char of pattern */
  register unsigned state,
		    lim = 0,
		    initial = ~((unsigned) 0);  /* one's compliment of zero */
  unsigned          t[MAXSYM],
		    i,
		    j,
		    matches = 0;                /* initialize to 0 */

  if (strlen(pattern) > WORD)
    fprintf(stderr, "Use pattern size <= word size\n");
  /* preprocessing */
  for (i = 0; i < MAXSYM; i++)
    t[i] = initial;                    /* set to one's compliment of zero */
  for (j = 1; *pattern != EOS; j <<= B)
    {
    t[*pattern] &= ~j;
    lim |= j;
    pattern++;
    }
  lim = ~(lim >> B);
  /* string search */
  do
    {
    while ((*text != EOS) && (*text != first))
      text++;                          /* scan for a matching char or EOS */
    state = initial;                   /* set initial state */
    do
      {
      state = ((state << B) | t[*text]);/* set next state */
      if (state < lim)
	matches++;                     /* match at currpos-len(pattern)+1 */
      text++;
      }
    while (state != initial);
    }
  while (*(text-1) != EOS);            /* check previous char for EOS */
  return(matches);
  }


/***************************************************************************
   function:str_match_sa()

 parameters:    text - text to be searched
	     pattern - string pattern to be searched for
		   k - the maximum number of mismatched characters allowed

    returns: The number of occurances of (pattern) in (text).

    purpose: Use to determine the number of occurances of a pattern in a
	     given string allowing for at most k mismatched characters.
	     The string matching code is a representation of the Shift-Add
	     algorithm presented by Baeza-Yates and Gonnet in "A New
	     Approach to Text Searching", Communications Of The ACM
	     (October 1992). I have made a few changes to the code to make
	     it more usable in application.
****************************************************************************/
unsigned str_match_sa(register char *text, char *pattern, int k)
  {
  char     type = MISMATCH;            /* type of search (MATCH or MISMATCH)*/
  int      m;
  unsigned mask,
	   lim,
	   ovmask = 0,
	   t[MAXSYM],
	   b,                          /* number of bits per state */
	   i,
	   state,
	   overflow,
	   matches = 0;

  m = strlen(pattern);
  if ((2 * k) > m)
    {
    type = MATCH;                       /* count matches */
    k = m - k;
    }
  b = clog2(k + 1) + 1;                 /* ceiling of log base 2 of k+1 */
  if (m > (WORD / b))
    fprintf(stderr, "Search does not work for this case.");
  /****** Preprocessing ******/
  lim = k << ((m - 1) * b);
  for (i = 1; i <= m; i++)
    ovmask = (ovmask << b) | (1 << (b-1));
  if (type == MATCH)
    for (i = 0; i < MAXSYM; i++)
       t[i] = 0;
  else
    {
    lim += 1 << ((m - 1) * b);
    for (i = 0; i < MAXSYM; i++)
      t[i] = ovmask >> (b - 1);
    }
  for (i = 1; *pattern != EOS; i <<= b)
    {
    if (type == MATCH)
      t[*pattern] += i;
    else
      t[*pattern] &= ~i;
    pattern++;
    }
  if ((m * b) == WORD)
    mask = ~((unsigned) 0);
  else
    mask = i - 1;
  /****** Searching ******/
  if (type == MATCH)                   /* initial state */
    {
    state    = 0;
    overflow = 0;
    }
  else
    {
    state    = mask & ~ovmask;
    overflow = ovmask;
    }
  for (; *text != EOS; text++)
    {
    state    = ((state << b) + t[*text]) & mask;
    overflow = ((overflow << b) | (state & ovmask)) & mask;
    state   &= ~ovmask;
    if (type == MATCH)
      {
      if ((state | overflow) >= lim)
	matches++;                     /* match with more than m-k errors */
      }
    else
      {
      if ((state | overflow) < lim)
	matches++;                     /* match with (state>>(m-1)*b)errors*/
      }
    }
  return(matches);
  }


/***************************************************************************
   function:clog2()

 parameters: x - operand of ceiling of log2(x)

    returns: log2(x) for x>0
	     0 for x<=0

    purpose: The ceiling function of log2(x).
****************************************************************************/
int clog2(int x)
  {
  int i = 0;

  while (x > (1 << i))
    i++;
  return(i);
  }

