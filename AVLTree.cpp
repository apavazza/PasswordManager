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
AVLTree* AVLTree::insertNodeAVL(std::string& name, std::string& username, std::string& password)
{
	AVLTree* n = this;
	if (!n)
	{
		return new AVLTree(name, username, password);

	}

	if (n->name > name)
	{
		n->left = n->left->insertNodeAVL(name, username, password);
		if (n->left->calcHeight() - n->right->calcHeight() == 2)
		{
			if (n->left->name > name) {
				n = n->llRotation();
			}
			else
			{
				n = n->lrRotation();
			}
		}
	}
	else if (n->name < name)
	{
		n->right = n->right->insertNodeAVL(name, username, password);
		if (n->right->calcHeight() - n->left->calcHeight() == 2)
		{
			if (n->right->name < name) {
				n = n->rrRotation();
			}
			else
			{
				n = n->rlRotation();
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
int AVLTree::calcHeight()
{
	if (!this) return 0;
	return std::max(this->left->calcHeight(), this->right->calcHeight()) + 1;
}

/*
* Right-right rotation.
* @return	Returns the address of the parent node.
*/
AVLTree* AVLTree::rrRotation()
{
	AVLTree* temp = this->right;
	this->right = temp->left;
	temp->left = this;
	return temp;
}

/*
* Left-left rotation.
* @return	Returns the address of the parent node.
*/
AVLTree* AVLTree::llRotation()
{
	AVLTree* temp = this->left;
	this->left = temp->right;
	temp->right = this;
	return temp;
}

/*
* Left-right rotation.
* @return	Returns the address of the parent node.
*/
AVLTree* AVLTree::lrRotation()
{
	AVLTree* temp = this->left;
	this->left = temp->rrRotation();
	return this->llRotation();
}

/*
* Right-left rotation.
* @return	Returns the address of the parent node.
*/
AVLTree* AVLTree::rlRotation()
{
	AVLTree* temp = this->right;
	this->right = temp->llRotation();
	return this->rrRotation();
}

/*
* Deletes a node from the tree.
* @param	nameToDelete	Name of the node to delete.
* @return					Returns the address of the parent node.
*/
AVLTree* AVLTree::deleteNode(std::string& nameToDelete)
{
	if (!this)
	{
		return nullptr;
	}

	if (this->name < nameToDelete)
	{
		this->right = this->right->deleteNode(nameToDelete);
	}
	else if (this->name > nameToDelete)
	{
		this->left = this->left->deleteNode(nameToDelete);
	}
	else
	{
		if (this->left)
		{
			AVLTree* temp = this->left->findMax();
			this->name = temp->name;
			this->username = temp->username;
			this->password = temp->password;
			this->left = this->left->deleteNode(temp->name);
		}
		else if (this->right)
		{
			AVLTree* temp = this->right->findMin();
			this->name = temp->name;
			this->username = temp->username;
			this->password = temp->password;
			this->right = this->right->deleteNode(temp->name);
		}
		else
		{
			delete(this);
			return nullptr;
		}
	}

	return this;
}

/*
* Finds the node with the maximum value.
* @return	Returns the address of the node with the maximum value.
*/
AVLTree* AVLTree::findMax()
{
	AVLTree* temp = this;
	if (temp)
	{
		while (temp->right)
		{
			temp = temp->right;
		}
		return temp;
	}

	return nullptr;
}

/*
* Finds the node with the minimum value.
* @return	Returns the address of the node with the minimum value.
*/
AVLTree* AVLTree::findMin()
{
	AVLTree* temp = this;
	if (temp)
	{
		while (temp->left)
		{
			temp = temp->left;
		}
		return temp;
	}

	return nullptr;
}

/*
* Finds a node with a certain value.
* @param nameToFind		Name of the node to search.
* @return				Returns the address of the node with a certain value.
*/
AVLTree* AVLTree::findNode(std::string& nameToFind)
{
	if (!this) throw std::runtime_error("Applicaton with this name does not exist");

	if (this->name > nameToFind)
	{
		return this->left->findNode(nameToFind);
	}
	else if (this->name < nameToFind)
	{
		return this->right->findNode(nameToFind);
	}

	return this;
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
std::string AVLTree::toString()
{
	if (!this) return "";
	std::stringstream buffer;
	buffer << "Application name: " << name << std::endl
		<< "Username: " << username << std::endl
		<< "Password: " << password << std::endl << std::endl;
	return buffer.str();
}

/*
* Prints all nodes.
*/
std::string AVLTree::allToString()
{
	if (!this) return "";
	std::stringstream buffer;
	buffer << this->left->allToString();
	buffer << this->toString();
	buffer << this->right->allToString();
	return buffer.str();
}

/*
* Deletes all nodes.
* @return	Returns the address of the root node.
*/
AVLTree* AVLTree::deleteAllNodes()
{
	if (!this) return nullptr;
	this->left->deleteAllNodes();
	this->right->deleteAllNodes();
	delete(this);
	return nullptr;
}

/*
* Saves a tree to a file.
* @param filename			Name of the file.
* @param masterPassword		Password used to encrypt the file.
*/
void AVLTree::saveToFile(std::string& filename, std::string& masterPassword)
{
	std::string buffer = this->parseToJSON();
	encryptAndSave(buffer, masterPassword, filename);
}

/*
* Parses a tree into JSON.
* @return	Returns JSON in a form of a string.
*/
std::string AVLTree::parseToJSON()
{
	std::stringstream buffer;
	buffer << "{" << std::endl << "\"entries\":{" << std::endl;
	this->entryToJSON(&buffer);

	buffer << "}" << std::endl << "}" << std::endl;

	return buffer.str();
}

/*
* Creates a new JSON entry.
* @param buffer		Buffer which stores the JSON. 
*/
void AVLTree::entryToJSON(std::stringstream* buffer)
{
	if (!this) return;
	*buffer << "{" << std::endl
		<< "\"name\":" << this->name << std::endl
		<< "\"username\":" << this->username << std::endl
		<< "\"password\":" << this->password << std::endl
		<< "}" << std::endl;
	this->left->entryToJSON(buffer);
	this->right->entryToJSON(buffer);
}

/*
* Loads a tree from a file.
* @param filename			Name of the file to open.
* @param masterPassword		Password used to decrypt the file.
* @return					Returns the address of the root node.
*/
AVLTree* AVLTree::loadFromFile(std::string& filename, std::string& masterPassword)
{
	std::string head[] = { "{", "\"entries\":{"};
	AVLTree* n = this;
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
			n = n->newEntry(&ssbuffer);
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
AVLTree* AVLTree::newEntry(std::stringstream* ssbuffer)
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
	return this->insertNodeAVL(name, username, password);
}