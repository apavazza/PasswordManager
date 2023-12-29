/*
* AVL Tree
*/
#include "AVLTree.h"

/*
* Constructor used to create new nodes in the tree.
* @param name		Name to assign to a node.
* @param username	Username to assign to a node.
* @param password	Password to assign to a node.
*/
AVLTree::AVLTree(std::string& name, std::string& username, std::string& password)
{
	this->name = name;
	this->username = username;
	this->password = password;
	this->left = nullptr;
	this->right = nullptr;
}

/*
* Inserts a new node into the tree.
* @param name		Name to assign to a node.
* @param username	Username to assign to a node.
* @param password	Password to assign to a node.
* @return			Returns the address of the parent node.
*/
AVLTree* AVLTree::insertNodeAVL(AVLTree* n, std::string& name, std::string& username, std::string& password)
{
	if (!n)
	{
		return new AVLTree(name, username, password);

	}

	if (n->name > name)
	{
		n->left = insertNodeAVL(n->left, name, username, password);
		if (calcHeight(n->left) - calcHeight(n->right) == 2)
		{
			if (n->left->name > name) {
				n = llRotation(n);
			}
			else
			{
				n = lrRotation(n);
			}
		}
	}
	else if (n->name < name)
	{
		n->right = insertNodeAVL(n->right, name, username, password);
		if (calcHeight(n->right) - calcHeight(n->left) == 2)
		{
			if (n->right->name < name) {
				n = rrRotation(n);
			}
			else
			{
				n = rlRotation(n);
			}
		}
	}
	else if (n->name == name)
	{
		throw std::runtime_error("An entry with this name already exists");
	}

	return n;
}

/*
* Calculates a node's height.
* @return	Returns the node's height.
*/
int AVLTree::calcHeight(AVLTree* n)
{
	if (!n) return 0;
	return std::max(calcHeight(n->left), calcHeight(n->right)) + 1;
}

/*
* Right-right rotation.
* @return	Returns the address of the parent node.
*/
AVLTree* AVLTree::rrRotation(AVLTree* n)
{
	AVLTree* temp = n->right;
	n->right = temp->left;
	temp->left = n;
	return temp;
}

/*
* Left-left rotation.
* @return	Returns the address of the parent node.
*/
AVLTree* AVLTree::llRotation(AVLTree* n)
{
	AVLTree* temp = n->left;
	n->left = temp->right;
	temp->right = n;
	return temp;
}

/*
* Left-right rotation.
* @return	Returns the address of the parent node.
*/
AVLTree* AVLTree::lrRotation(AVLTree* n)
{
	AVLTree* temp = n->left;
	n->left = rrRotation(temp);
	return llRotation(n);
}

/*
* Right-left rotation.
* @return	Returns the address of the parent node.
*/
AVLTree* AVLTree::rlRotation(AVLTree* n)
{
	AVLTree* temp = n->right;
	n->right = llRotation(temp);
	return rrRotation(n);
}

/*
* Deletes a node from the tree.
* @param	nameToDelete	Name of the node to delete.
* @return					Returns the address of the parent node.
*/
AVLTree* AVLTree::deleteNode(AVLTree* n, std::string& nameToDelete)
{
	if (!n)
	{
		return nullptr;
	}

	if (n->name < nameToDelete)
	{
		n->right = deleteNode(n->right, nameToDelete);
	}
	else if (n->name > nameToDelete)
	{
		n->left = deleteNode(n->left, nameToDelete);
	}
	else
	{
		if (n->left)
		{
			AVLTree* temp = findMax(n->left);
			n->name = temp->name;
			n->username = temp->username;
			n->password = temp->password;
			n->left = deleteNode(n->left, temp->name);
		}
		else if (n->right)
		{
			AVLTree* temp = findMin(n->right);
			n->name = temp->name;
			n->username = temp->username;
			n->password = temp->password;
			n->right = deleteNode(n->right, temp->name);
		}
		else
		{
			delete(n);
			return nullptr;
		}
	}

	return n;
}

/*
* Finds the node with the maximum value.
* @return	Returns the address of the node with the maximum value.
*/
AVLTree* AVLTree::findMax(AVLTree* n)
{
	if (n)
	{
		while (n->right)
		{
			n = n->right;
		}
		return n;
	}

	return nullptr;
}

/*
* Finds the node with the minimum value.
* @return	Returns the address of the node with the minimum value.
*/
AVLTree* AVLTree::findMin(AVLTree* n)
{
	if (n)
	{
		while (n->left)
		{
			n = n->left;
		}
		return n;
	}

	return nullptr;
}

/*
* Finds a node with a certain value.
* @param nameToFind		Name of the node to search.
* @return				Returns the address of the node with a certain value.
*/
AVLTree* AVLTree::findNode(AVLTree* n, std::string& nameToFind)
{
	if (!n) throw std::runtime_error("Applicaton with this name does not exist");

	if (n->name > nameToFind)
	{
		return findNode(n->left, nameToFind);
	}
	else if (n->name < nameToFind)
	{
		return findNode(n->right, nameToFind);
	}

	return n;
}

/*
* Sets the node's username to a new value.
*/
void AVLTree::setUsername(std::string& newUsername)
{
	username = newUsername;
}

/*
* Sets the node's password to a new value.
*/
void AVLTree::setPassword(std::string& newPassword)
{
	password = newPassword;
}

/*
* Prints the node.
*/
std::string AVLTree::toString(AVLTree* n)
{
	if (!n) return "";
	std::stringstream buffer;
	buffer << "Application name: " << n->name << std::endl
		<< "Username: " << n->username << std::endl
		<< "Password: " << n->password << std::endl << std::endl;
	return buffer.str();
}

/*
* Prints all nodes.
*/
std::string AVLTree::allToString(AVLTree* n)
{
	if (!n) return "";
	std::stringstream buffer;
	buffer << allToString(n->left);
	buffer << toString(n);
	buffer << allToString(n->right);
	return buffer.str();
}

/*
* Deletes all nodes.
* @return	Returns the address of the root node.
*/
AVLTree* AVLTree::deleteAllNodes(AVLTree* n)
{
	if (!n) return nullptr;
	deleteAllNodes(n->left);
	deleteAllNodes(n->right);
	delete(n);
	return nullptr;
}

/*
* Saves a tree to a file.
* @param filename			Name of the file.
* @param masterPassword		Password used to encrypt the file.
*/
void AVLTree::saveToFile(AVLTree* n, std::string& filename, std::string& masterPassword)
{
	std::string buffer = parseToJSON(n);
	encryptAndSave(buffer, masterPassword, filename);
}

/*
* Parses a tree into JSON.
* @return	Returns JSON in a form of a string.
*/
std::string AVLTree::parseToJSON(AVLTree* n)
{
	std::stringstream buffer;
	buffer << "{" << std::endl << "\"entries\":{" << std::endl;
	entryToJSON(n, &buffer);
	buffer << "}" << std::endl << "}" << std::endl;

	return buffer.str();
}

/*
* Creates a new JSON entry.
* @param buffer		Buffer which stores the JSON. 
*/
void AVLTree::entryToJSON(AVLTree* n, std::stringstream* buffer)
{
	if (!n) return;
	*buffer << "{" << std::endl
		<< "\"name\":" << n->name << std::endl
		<< "\"username\":" << n->username << std::endl
		<< "\"password\":" << n->password << std::endl
		<< "}" << std::endl;
	entryToJSON(n->left, buffer);
	entryToJSON(n->right, buffer);
}

/*
* Loads a tree from a file.
* @param filename			Name of the file to open.
* @param masterPassword		Password used to decrypt the file.
* @return					Returns the address of the root node.
*/
AVLTree* AVLTree::loadFromFile(AVLTree* n, std::string& filename, std::string& masterPassword)
{
	std::string head[] = { "{", "\"entries\":{"};
	std::string buffer;
	
	buffer = loadAndDecrypt(masterPassword, filename);
	std::stringstream ssbuffer(buffer);
	buffer.clear();

	for (size_t i = 0; i < 2; i++)
	{
		ssbuffer >> buffer;
		if (buffer != head[i]) throw std::runtime_error("Invalid file foramt");
	}
	ssbuffer >> buffer;
	if (buffer == "{")
	{
		while (buffer == "{")
		{
			n = newEntry(n, &ssbuffer);
			ssbuffer >> buffer;
			if (buffer != "}") throw std::runtime_error("Invalid file foramt");
			ssbuffer >> buffer;
		}
		for (size_t i = 0; i < 2; i++)
		{
			if (buffer != "}") throw std::runtime_error("Invalid file foramt");
			ssbuffer >> buffer;
		}
	}
	else if (buffer == "}")
	{
		ssbuffer >> buffer;
		if(buffer != "}") throw std::runtime_error("Invalid file foramt");
	}
	else throw std::runtime_error("Invalid file foramt");
	
	return n;
}

/*
* Parses an entry from JSON to a node in a tree.
* @param fileStream		Input file stream.
* @return				Returns the root node.
*/
AVLTree* AVLTree::newEntry(AVLTree* n, std::stringstream* ssbuffer)
{
	std::string buffer, name, username, password, tokenType, tokenValue;
	for (size_t i = 0; i < 3; i++)
	{
		*ssbuffer >> buffer;
		tokenType = buffer.substr(0, buffer.find(":"));
		tokenValue = buffer.substr(buffer.find(":") + 1);
		if (tokenType == "\"name\"")
		{
			name = tokenValue;
		}
		else if (tokenType == "\"username\"")
		{
			username = tokenValue;
		}
		else if (tokenType == "\"password\"")
		{
			password = tokenValue;
		}
		else throw std::runtime_error("Invalid file foramt");
	}
	return insertNodeAVL(n, name, username, password);
}