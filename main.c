#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "buildTree.h"
#include "treeStructure.h"
#include "writeTree.h"
int addednumber=0,removednumber=0;
int main( int argc, char **argv ) {

  Node *head;

  // make the head node
  head = makeNode( 0.0,0.0, 0 );

  // make a tree
  growTree( head );
  growTree( head );
   //removeChildren( head -> child[0]);
  growTree( head );
  // print the tree for Gnuplot
  get_flag( head );
  add_or_remove(head);
  printf( "%d nodes are added and %d nodes are removed",addednumber,removednumber);
  writeTree( head );
  destroyTree( head );
  return 0;
}
