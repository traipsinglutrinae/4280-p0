//CS4280
//Ian Lofton Green
//P0

#include <iostream>
#include <unordered_set>
#include "node.h"
#include "tree.h"

using namespace std;

//Traversal: inOrder
void printInorder(TREE *node, string printFile) {
	ofstream streamFile;
	streamFile.open(printFile.c_str(), std::ofstream::out | std::ofstream::app);
	if (!streamFile.is_open()) {
		perror("Error opening output file for in order traversal");
		return;
	}
	if (node == NULL) {
		streamFile.close();
		return;
	}
	else {
		printInorder(node->lhs, printFile);
		//Display and file output
		for (int n = 0; n < node->treeLevel; n++) {
			cout << "**";
			streamFile << "**";
		}
		cout << node->content << ":  ";
		streamFile << node->content << ":  ";
		for (int n = 0; n < node->list.size(); n++) {
			cout << node->list[n] << " ";
			streamFile << node->list[n] << " ";
		}
		cout << endl;
		streamFile << "\n";
		printInorder(node->rhs, printFile);
	}
	streamFile.close();
}
//Traversal: preOrder
void printPreorder(TREE *node, string printFile) {
	ofstream streamFile;
	streamFile.open(printFile.c_str(), std::ofstream::out | std::ofstream::app);
	if (!streamFile.is_open()) {
		perror("Error opening output file for pre order traversal");
		return;
	}
	if (node == NULL) {
		streamFile.close();
		return;
	}
	else {
		//Display and file output
		for (int n = 0; n < node->treeLevel; n++) {
			cout << "**";
			streamFile << "**";
		}
		cout << node->content << ":  ";
		streamFile << node->content << ":  ";
		for (int n = 0; n < node->list.size(); n++) {
			cout << node->list[n] << " ";
			streamFile << node->list[n] << " ";
		}
		cout << endl;
		streamFile << "\n";
		printPreorder(node->lhs, printFile);
		printPreorder(node->rhs, printFile);
	}
	streamFile.close();
}
//Traversal: postOrder
void printPostorder(TREE *node, string printFile) {
	ofstream streamFile;
	streamFile.open(printFile.c_str(), std::ofstream::out | std::ofstream::app);
	if (!streamFile.is_open()) {
		perror("Error opening output file for post order traversal");
		return;
	}
	if (node == NULL) {
		streamFile.close();
		return;
	}
	else {
		printPostorder(node->lhs, printFile);
		printPostorder(node->rhs, printFile);
		//Display and file output
		for (int n = 0; n < node->treeLevel; n++) {
			cout << "**";
			streamFile << "**";
		}
		cout << node->content << ":  ";
		streamFile << node->content << ":  ";
		for (int n = 0; n < node->list.size(); n++) {
			cout << node->list[n] << " ";
			streamFile << node->list[n] << " ";
		}
		cout << endl;
		streamFile << "\n";
	}
	streamFile.close();
}

//Create a node
TREE *create(string input) {
	TREE *ephemoral = new TREE;
	ephemoral->content = input.size();
	ephemoral->list.push_back(input);
	ephemoral->treeLevel = 0;
	ephemoral->lhs = NULL;
	ephemoral->rhs = NULL;
	return ephemoral;
}

//Insert a node into the tree
TREE *insert(TREE *node, string input) {
	int inSize = input.size();
	if (!node) {
		node = create(input);	//NDE
		//cout << "New" << endl;	//diagnostic output
	}	
	else if (inSize < node->content) {	//insert lhs
		node->lhs = insert(node->lhs, input);
		node->lhs->treeLevel = (node->treeLevel + 1);	//update depth
		//cout << "Added to LHS" << endl;	//diagnostic output
	}	
	
	else if (inSize == node->content) {
		node->list.push_back(input);	//add to list
		//cout << "Added to existing node" << endl;	//diagnostic output
	}
	else {// if (inSize > node->content) {	//insert rhs
		node->rhs = insert(node->rhs, input);
		node->rhs->treeLevel = (node->treeLevel + 1);	//update depth
		//cout << "Added to RHS" << endl;	//diagnostic output
	}
	return node;
}

//Build the tree
TREE *buildTree(string inputFile) {
	ifstream source(inputFile.c_str());
	if (source.is_open()) {
		cout << "Input data file opened" << endl;
	}
	else {
		perror("Error opening data file");
		return NULL;
	}
	TREE *rootNode = NULL;
	string ephemoral;
	while (source >> ephemoral) {
		bool ephVal = false;
		
		//Ensure all letters
		for (int n = 0; n < ephemoral.size(); n++) {
			if (ispunct(ephemoral.at(n))) {
				perror("Error: Input element is a special character");	//diagnostic output
				return NULL;
			}
			else if (isblank(ephemoral.at(n))) {
				perror("Error: Input element is a blank space");	//diagnostic output
				return NULL;
			}
			else if (isalpha(ephemoral.at(n)) || isdigit(ephemoral.at(n))) {
				ephVal = true;
			}
			else {
				perror("Error: Input element is unknown");	//diagnostic output
				return NULL;
			}
		}
		if (ephVal == true) {
			rootNode = insert(rootNode, ephemoral);	//add the node
		}
	}
	source.close();
	cout << "Input validated and accepted" << endl;
	return rootNode;
}


