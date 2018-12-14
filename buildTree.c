#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "buildTree.h"
#include "treeStructure.h"
Node *makeNode( double x, double y, int level ) {

  int i;

  Node *node = (Node *)malloc(sizeof(Node));

  node->level = level;

  node->xy[0] = x;
  node->xy[1] = y;

  for( i=0;i<4;++i )
    node->child[i] = NULL;

  return node;
}

// split a leaf nodes into 4 children

void makeChildren( Node *parent ) {

  double x = parent->xy[0];
  double y = parent->xy[1];

  int level = parent->level;

  double hChild = pow(2.0,-(level+1));

  parent->child[0] = makeNode( x,y, level+1 );
  parent->child[1] = makeNode( x+hChild,y, level+1 );
  parent->child[2] = makeNode( x+hChild,y+hChild, level+1 );
  parent->child[3] = makeNode( x,y+hChild, level+1 );

  return;
}

void growTree(Node *node){

  int i=0;
  if( node-> child[0] == NULL ){
    makeChildren(node);
  }
  else{
    for(i=0;i<4;i++){
        growTree( node-> child[i]);
    }
  }
}

void destroyTree(Node *node){

    int i=0;
    if( node->child[0] == NULL ){
        free(node);
        node=NULL;
    }
    else{
        for(i=0;i<4;i++){
            destroyTree(node -> child[i]);
        }
	free(node);
    }
}

void removeChildren(Node *parent){

     int i=0;
     for( i=0 ; i<4 ; i++){
	     free(parent->child[i]);	
		parent->child[i]=NULL;
     }
}


// Evaluate function at centre of quadtree node

double nodeValue( Node *node, double time ) {

  int level = node->level;
  double x = node->xy[0];
  double y = node->xy[1];

  double h = pow(2.0,-level);

  return( value( x+0.5*h, y+0.5*h, time ) );
}

// Data function

double value( double x, double y, double time ) {

  return( 2.0*exp(-8.0*(x-time)*(x-time)) - 1.0 ) ;
}

void get_flag( Node *node){
	int i;
	if( node -> child[0] == NULL){
		if( nodeValue( node,0.0 )<-0.5){
			node -> flag = -1;
		}
		else if(nodeValue( node,0.0 )>0.5){
			node -> flag = 1;
		}		
	}
	else{
		node -> flag = 0;
		for(i=0;i<4;i++){
			get_flag( node -> child[i]);
		}
	}
}

void add_or_remove(Node *node){
	int i;
	int n;
	n = 0;
	extern int addednumber,removednumber;
	if( node -> child[0] == NULL){
		if( node -> flag ==1){
			makeChildren( node );
			get_flag( node );
			addednumber += 4;
		}}
	else{
		for(i=0;i<4;i++){
			if(node -> child[i] -> flag == -1){
				n++;
			}
			else{
				n = 0;
			}
		}
		if( n == 4){
			removeChildren( node );
			get_flag( node );
			removednumber += 4;
		}
		else{
			for(i=0;i<4;i++){
				add_or_remove( node -> child[i]);
			}
		}
	}
}
