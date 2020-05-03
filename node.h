//CS4280
//Ian Lofton Green
//P0

#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;
typedef struct node {
	node *lhs;	//left hand side
	node *rhs;	//right hand side
	int treeLevel;
	int content;
	vector<string> list;
} TREE;

#endif
