/* set.h

   By Michael W. Maher

   Ver 1.0 6/12/92      for MCS 5.1
   Ver 1.5 8/18/92

   This is the header file for Set.C
   Programming tools written in Microsoft C ver 5.1.

   Set functions and data types.

   ******************* Abstract Data Type Description (ADTD) ****************
   SET
	Properties:
		1. A set is a collection of things.
		2. A set can have NO duplicates.
		3. A set having no elements is an empty set.
		4. The elements in a set have NO implied order.
		5. A set has NO membership restrictions (except rule 6).
		   e.g. sets of sets, sets of integers, sets of floats,...
		6. A single set can not contain dissimilar types; e.g.
		   a set with an integer, float, and a char.
		   (It is possible to break this rule since it really is not
		    a part of the mathematical definition.  With some
		    creativity and a good reason to do so it could be done.)

	Operators:
		add()
		set_del_elem()
		set_union()
		set_intersection()
		set_symmetric_difference()
		set_compare()
		is_an_element()
		is_empty()
		set_size()
		element_comparison_function()    NOTE: user defined function!

	Data Types:
		sets     : a set is a struct type set_type
		elements : a void ptr to any data type
*/

#ifndef SETH
  #define SETH

  /* includes */
  #include<malloc.h>
  #include<stdlib.h>
  #include"toolkit.h"

  /* **************************** macros ********************************* */

  /* ************************** definitions ****************************** */

  /* ******************* fundamental structure types ********************* */
  typedef struct set_type
    {
    char (*comp_ele)(void *ele1,
		     void *ele2);      /* ptr to comparison function */
    struct dl_node *start;             /* a ptr to the start of the set */
    unsigned long elements;            /* the number of elements in a set */
    struct dl_node *curr_pos;          /* current position of search */
    } set_type;

  /* *********************** function prototypes ************************* */

  /* add an element to a set */
  char add(set_type *setdata, void *element);

  /* delete an element from a set */
  char set_del_elem(set_type *setdata, void *element);

  /* combine the elements of two sets without duplicates */
  char set_union(set_type *set1, set_type *set2, set_type *result);

  /* combine the like elements in two sets into a single result */
  char set_intersection(set_type *set1, set_type *set2, set_type *result);

  /* combine the elements that are unique in each set into a single result */
  char set_symmetric_difference(set_type *set1, set_type *set2, set_type *result);

  /* compare two sets for equality, return TRUE is equal, FALSE if unequal */
  char set_compare(set_type *set1, set_type *set2);

  /* check to see if an element is a member of a set */
  char is_an_element(set_type *setdata, void *element);

  /* check a set for the existance of elements */
  char is_empty(set_type *setdata);

  /* returns the number of elements in a set as an unsigned long integer */
  unsigned long set_size(set_type *setdata);

  /* compare two integers; 0 if equal, 1 if 1 is greater than 2, -1 if less */
  char comp_integers(void *element1, void *element2);

  #endif


