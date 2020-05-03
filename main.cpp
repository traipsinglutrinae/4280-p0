//CS4280
//Ian Lofton Green
//P0

#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "node.h"
#include "tree.h"

using namespace std;

int main(int argc, char *argv[]) {
	string userFile;
	string printFile;	
	//User entered input file
	if (argc == 2) {
		userFile = argv[1];
		printFile = argv[1];
		userFile.append(".sp2020");
		cout << "----------" << endl;
		cout << "Input File: " << userFile << endl;
		cout << "----------" << endl;
		cout << "Words in input: " << endl;
		string line;
		ifstream file (userFile.c_str());
		if (file.is_open()) {
			while (getline(file, line)) {
				if ( (!line.empty()) && (line[line.length()-1] == '\n') ) {
					line.erase(line.length()-1);
				}
				cout << line << ", ";
			}
			file.close();
			cout << "\n----------" << endl;
		}
		else {
			perror("Error opening user supplied input file");
			return 1;
		}
	}

	//Interactive user input
	else if (argc == 1) {
		cout << "Interactive User Input Mode:" << endl;
		string userInput;
		userFile = "inputStream.sp2020";
		printFile = "output";
		ofstream streamFile;
		streamFile.open(userFile.c_str());
		
		//Capture user keyboard input
		if (streamFile.is_open()) {
			cout << "Stream File Creation Successful" << endl;
			cout << "Please enter characters/words one at a time. Press CTRL-D to finish interactive input." << endl;
			while ( cin >> userInput) {
				streamFile << userInput << "\n";
			}
			streamFile.close();
			cout << "----------" << endl;
			cout << "Input saved to: " << userFile << endl;
			cout << "--------------" << endl;
			cout << "Words in input: " << endl;
			string line;
			ifstream file (userFile.c_str());
			if (file.is_open()) {
				while (getline(file, line)) {
					if ( (!line.empty()) && (line[line.length()-1] == '\n') ) {
						line.erase(line.length()-1);
					}
					cout << line << ", ";
				}
				file.close();
				cout << "\n----------" << endl;
			}
		}
		else {
			perror("Error Creating Stream File");
			return 1;
		}
	}

	//Input error
	else {
		perror("Error executing program.");
		return 1;
	}
	
	//Clear duplicates
	ifstream inFile (userFile.c_str());
	ofstream outFile ("cleanedInput.sp2020");
	map<string,int> wordMap;
	string current;
	if (inFile.is_open()) {
		if (outFile.is_open()) {
			while (getline(inFile, current)) {
				if (wordMap[current] == NULL) {
					wordMap[current] = 1;
					outFile.write(current.c_str(), current.length());
					outFile.put('\n');
				}
				else {
					wordMap[current]++;
				}
			}
			inFile.close();
			outFile.close();
			remove("inputStream.sp2020");
			userFile = "cleanedInput.sp2020";
		}
		else {
			perror("Error opening output file for cleaned input");
			return 1;
		}
	}
	else {
		perror("Error opening file to clean");
		return 1;
	}

	//Do tree stuff
	TREE *rootNode = buildTree(userFile);
	cout << "----------" << "InOrder" << endl;
	string tempPrintFile = printFile;
	tempPrintFile.append(".inorder");
	ofstream touchFile(tempPrintFile.c_str());
	touchFile.close();
	printInorder(rootNode, tempPrintFile);
	
	cout << "----------" << "PreOrder" << endl;
	tempPrintFile = printFile;
	tempPrintFile.append(".preorder");
	printPreorder(rootNode, tempPrintFile);

	cout << "----------" << "\nPostOrder" << endl;
	tempPrintFile = printFile;
	tempPrintFile.append(".postorder");
	printPostorder(rootNode, tempPrintFile);

	remove("cleanedInput.sp2020");
}
