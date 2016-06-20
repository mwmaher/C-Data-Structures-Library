/* BTree.h

   By Michael W. Maher
   Ver 1.0 6/19/92

   DESCRIPTION: This is the header file for BTree.C
		B-Tree functions and data types.


   Abstract Data Type Description (ADTD).

   B-Tree
	Properties:
		0. The "B" in B-tree does not stand for binary.  Though it
		might possibly stand for "bushy" or "balanced".

		1. A B-tree of order d is defined as tree with the following
		characteristics:
			a. The tree is homogeneous; meaning that all tree
			ptrs are of the same type.

			b. Each node can hold a maximum of 2d data pointers
			and 2d+1 tree pointers.

			c. The only node that can have fewer than d keys
			is the root.

			d. Leaf nodes must all be on the same level.

		2. (d+1) <= fan-out factor => (2d+1)


	Operators:
		b_add()
		b_delete()
		b_find()

	Data Types:
		MY_B_TREE_ORDER - can be used by the user to set the order of
		the B-tree at compile type if this preprocessor directive
		is not set the default is 1.

		t_node          - a tree node struct

		btree_type      - a B-tree struct
*/


#ifndef BTREEH
  #define BTREEH

  /* includes */
  #include<malloc.h>
  #include<stdlib.h>
  #include"toolkit.h"

  /* macros */
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
  #endif

  /* setting the order of the B-tree with preprocessor directives */
  #ifndef MY_B_TREE_ORDER
    TREE_ORDER 1                       /* Default B-tree order of 1 */
  #endif
  #ifndef TREE_ORDER
    TREE_ORDER MY_B_TREE_ORDER         /* user may define B-tree order */
  #endif


  /* fundamental structure types */

  /* tree node structure */
  /* a slightly larger node buffer is used for overflow management */
  typedef struct t_node
    {
    struct t_node *tree[(2*T_ORDER)+1];/* tree ptrs */
    void       *data[(2*TREE_ORDER)+2];/* ptrs to data */
    }

  /* B-tree struct */
  typedef struct btree_type
    {
    char (*comp_nodes)
	 (void *nod1, void *nod2);     /* ptr to a comparison function */
    t_node *root;                      /* root node of the b-tree */
    } btree_type;


  /* function prototypes */

  /* user functions */
  /* add a data item to a btree */
  char b_add(btree_type *btree, void *data);

  /* delete (remove) an item from a btree */
  char b_delete(btree_type *btree, void *data);

  /* finds and returns a data ptr from a B-tree, returns NULL if no match */
  void *b_find(btree_type *btree, l_node *node, void *data);

  /* an in-order B-tree traversal, reads all data items in order */
  void *b_traverse(btree_type *btree, l_node *node, void *lo, void *hi);

  /* function internal to B-tree user functions */
  /* builds node_stack such that top entry is the first item >= lo */
  void *b_find_first(btree_type *btree,
		     void *lo,
		     l_node *node,
		     stack_type *node_stack);

  /* returns a ptr to next data item if there is one within range else NULL */
  void *b_get_next(btree_type *btree, void *hi, stack_type *node_stack);

  /* check the B-tree for an overflow condition, the add function uses */
  char b_overflow_check(btree_type *btree, l_node *node);

  /* check the B-tree for an underflow condition, the delete function uses */
  char b_underflow_check(btree_type *btree, l_node *node);

  #endif
