//CS4280
//Ian Lofton Green
//P0

#ifndef TREE_H
#define TREE_H

#include <fstream>
#include <string>
#include "node.h"

void printInorder(TREE *, string);
void printPreorder(TREE *, string);
void printPostorder(TREE *, string);

TREE *create(string);
TREE *insert(TREE, string);
TREE *buildTree(string);

#endif
