/*
* Password Manager
*/
#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include "AVLTree.h"
#include "AES-CBC.h"
#include "mode.h"
#include "command.h"

void startMenu(bool argsPassed, int choice, std::string argFilename);
void entriesMenu(AVLTree* root, std::string& filename, std::string& masterPassword);
void printstartMenu();
void printEntriesMenu();
void passwordPrompt(std::string& password);