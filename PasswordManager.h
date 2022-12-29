/*
* Password Manager
*/
#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include "AVLTree.h"
#include "AES-CBC.h"

void startMenu();
bool entriesMenu(AVLTree* root, std::string& filename, std::string& masterPassword);
void printstartMenu();
void printEntriesMenu();