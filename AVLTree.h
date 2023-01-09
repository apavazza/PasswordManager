/*
* AVL Tree
*/

#pragma once
#include <string>
#include <sstream>
#include "AES-CBC.h"

class AVLTree
{
public:
	AVLTree(std::string& name, std::string& username, std::string& password);
	static AVLTree* insertNodeAVL(AVLTree* n, std::string& name, std::string& username, std::string& password);
	static AVLTree* deleteNode(AVLTree* n, std::string& nameToDelete);
	static AVLTree* findNode(AVLTree* n, std::string& nameToFind);
	void setUsername(std::string& newUsername);
	void setPassword(std::string& newPassword);
	static std::string toString(AVLTree* n);
	static std::string allToString(AVLTree* n);
	static AVLTree* deleteAllNodes(AVLTree* n);
	static void saveToFile(AVLTree* n, std::string& filename, std::string& masterPassword);
	static AVLTree* loadFromFile(AVLTree* n, std::string& filename, std::string& masterPassword);

private:
	std::string name, username, password;
	AVLTree *left, *right;

	static int calcHeight(AVLTree* n);
	static AVLTree* findMax(AVLTree* n);
	static AVLTree* findMin(AVLTree* n);
	static AVLTree* rrRotation(AVLTree* n);
	static AVLTree* llRotation(AVLTree* n);
	static AVLTree* lrRotation(AVLTree* n);
	static AVLTree* rlRotation(AVLTree* n);
	static std::string parseToJSON(AVLTree* n);
	static void entryToJSON(AVLTree* n, std::stringstream* buffer);
	static AVLTree* newEntry(AVLTree* n, std::stringstream* fileStream);
};

