/* Toolkit.h

   By Michael W. Maher

   Ver 1.0 4/5/91     MCS 5.1
   Ver 1.5 8/18/92
   Ver 2.0 9/10/92    Two functions were added to the suite.  The new
		      functions support linked-lists and doubly-linked
		      lists.  The functions added
		      were: reverse_l_list() and reverse_dl_list()

   This is the header file for Toolkit.C.

   The toolkit was developed as an aid to C programmers.  The toolkit is
   full ANSI standard C.  The programs were tested with Microsoft C V5.1.
*/

#ifndef TOOLKITH
  #define TOOLKITH

  /******************************* includes ********************************/


  /******************************** macros *********************************/

  /******************************** defines ********************************/
  #ifndef BOOLEAN_DEFINE
    #define BOOLEAN_DEFINE
    #define TRUE 1
    #define FALSE 0
    #define ON 1
    #define OFF 0
    #define YES 1
    #define NO 0
    #define HOT 1
    #define COLD 0
    #define PASS 1
    #define FAIL 0
    #define RIGHT 1
    #define WRONG 0
    #define UP 1
    #define DOWN 0
  #endif

  /************************** structure types ******************************/
  /* linked node (for use in a linked list) */
  typedef struct l_node
    {
    void *data;                        /* a ptr to a data element */
    struct l_node *next;               /* ptr to next node in list */
    } l_node;

  /* doubly-linked node (for use in a doubly-linked list) */
  typedef struct dl_node
    {
    struct dl_node *prev;               /* ptr to previous node in list */
    void *data;                         /* a ptr to a data element */
    struct dl_node *next;               /* ptr to next node in list */
    } dl_node;


  /************************ function prototypes ****************************/

  /* list functions */
  /* reverses the direction of the ptrs in a doubly linked list */
  void reverse_dl_list(dl_node *list);

  /* reverses the direction of the ptrs in a linked list */
  void reverse_l_list(l_node *list);


  /* mathematical functions */

  /* Calculates x to the power y.  Recursive function.
  unsigned long power(unsigned long x, unsigned long y);

  /* Calculates the factorial of x. Recursive function. */
  unsigned long fact(unsigned long x);

#endif
