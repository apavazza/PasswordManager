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
	AVLTree* insertNodeAVL(std::string& name, std::string& username, std::string& password);
	AVLTree* deleteNode(std::string& nameToDelete);
	AVLTree* findNode(std::string& nameToFind);
	void setUsername(std::string& newUsername);
	void setPassword(std::string& newPassword);
	std::string toString();
	std::string allToString();
	AVLTree* deleteAllNodes();
	void saveToFile(std::string& filename, std::string& masterPassword);
	AVLTree* loadFromFile(std::string& filename, std::string& masterPassword);

private:
	std::string name, username, password;
	AVLTree *left, *right;

	int calcHeight();
	AVLTree* findMax();
	AVLTree* findMin();
	AVLTree* rrRotation();
	AVLTree* llRotation();
	AVLTree* lrRotation();
	AVLTree* rlRotation();
	std::string parseToJSON();
	void entryToJSON(std::stringstream* buffer);
	AVLTree* newEntry(std::stringstream* fileStream);
};

