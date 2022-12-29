/*
* AVL Tree
*/

#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include "AES-CBC.h"

class AVLTree
{
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

public:
	AVLTree(std::string& name, std::string& username, std::string& password);
	AVLTree* insertNodeAVL(std::string& name, std::string& username, std::string& password);
	AVLTree* deleteNode(std::string& nameToDelete);
	AVLTree* findNode(std::string& nameToFind);
	void setUsername(std::string& newUsername);
	void setPassword(std::string& newPassword);
	void print();
	void printAll();
	AVLTree* deleteAllNodes();
	void saveToFile(std::string& filename, std::string& masterPassword);
	AVLTree* loadFromFile(std::string& filename, std::string& masterPassword);
};

