#include "treeStructure.h"
#ifndef BUILDTREE_H
#define BUILDTREE_H
Node *makeNode( double x, double y, int level );
void makeChildren( Node *parent );
void growTree(Node *node);
void destroyTree(Node *node);
void removeChildren(Node *parent);
double nodeValue( Node *node, double time );
double value( double x, double y, double time );
void get_flag( Node *node);
void add_or_remove(Node *node);
#endif
