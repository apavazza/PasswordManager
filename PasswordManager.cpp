/*
* Password Manager
* Built using AVL trees.
*/
#include "PasswordManager.h"

int main(int argc, char* argv[])
{
	try {
		switch (argc)
		{
		case 1: // no arguments passed
			startMenu(false, 0, "");
			break;
		case 3: // arguments passed
			if (strcmp(argv[1], "-n") == 0) // create a new file
			{
				startMenu(true, 2, std::string(argv[2]));
			}
			else if (strcmp(argv[1], "-o") == 0) // opena a file
			{
				startMenu(true, 1, std::string(argv[2]));
			}
			else
			{
				throw std::invalid_argument("Invalid arguments passed");
			}
			break;
		default:
			throw std::invalid_argument("Invalid arguments passed");
			break;
		}
	}
	catch (std::invalid_argument& ia)
	{
		std::cerr << ia.what() << std::endl;
	}
	return EXIT_SUCCESS;
}

/*
* Provides the start menu.
*/
void startMenu(bool argsPassed, int choice, std::string argFilename)
{
	std::string filename, masterPassword;
	AVLTree* root = nullptr;
	bool status = false;
	std::cout << "Password Manager" << std::endl << std::endl;
	if(!argsPassed) printstartMenu();

	do {
		if (!argsPassed)
		{
			std::cout << " > ";
			std::cin >> choice;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				choice = 0;
			}
		}
		switch (choice)
		{
		case 1: // Open an existing database
			if (!argsPassed)
			{
				std::cout << "File name: ";
				std::cin >> filename;
			}
			else
			{
				filename = argFilename;
			}
			std::cout << "Password: ";
			std::cin >> masterPassword;
			try {
				root = root->loadFromFile(filename, masterPassword); //throws runtime_error
				status = entriesMenu(root, filename, masterPassword);
			}
			catch (std::runtime_error& re)
			{
				std::cerr << re.what() << std::endl;
				choice = 0;
			}
			catch (std::exception&)
			{
				std::cerr << "Could not open file '" + filename + "'" << std::endl;
				if (argsPassed) break;
				choice = 0;
			}
			break;
		case 2: // Create a new database
			if (!argsPassed)
			{
				std::cout << "File name: ";
				std::cin >> filename;
			}
			else
			{
				filename = argFilename;
			}
			std::cout << "Create a password: ";
			std::cin >> masterPassword;
			status = entriesMenu(root, filename, masterPassword);
			// FALLTHROUGH
		case 3:
			// Quitting application
			break;
		default:
			printstartMenu();
			std::cout << "Input not recognised, please try again" << std::endl;
			break;
		}
	} while (choice != 1 && choice != 2 && choice != 3 && !status);

	std::cout << "Quitting application..." << std::endl;
}

/*
* Provides the menu used for managing entries in the database.
*/
bool entriesMenu(AVLTree* root, std::string& filename, std::string& masterPassword)
{
	printEntriesMenu();

	while (true)
	{
		try {
			int choice;
			std::string name, username, password;
			AVLTree* temp;
			std::cout << " > ";
			std::cin >> choice;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				choice = 0;
			}
			switch (choice)
			{
			case 1: // List all entries
				root->printAll();
				break;
			case 2: // find an entry
				std::cout << "Enter application name to search: ";
				std::cin >> name;
				root->findNode(name)->print();
				break;
			case 3: // add an entry
				std::cout << "Enter application name: ";
				std::cin >> name;
				std::cout << "Enter username: ";
				std::cin >> username;
				std::cout << "Enter password: ";
				std::cin >> password;
				root = root->insertNodeAVL(name, username, password); //throws runtime_error
				break;
			case 4: // delete an entry
				std::cout << "Application name to delete: ";
				std::cin >> name;
				root = root->deleteNode(name); //balance
				break;
			case 5: // update username
				std::cout << "Enter application name: ";
				std::cin >> name;
				temp = root->findNode(name);
				std::cout << "Enter new username: ";
				std::cin >> username;
				temp->setUsername(username);
				break;
			case 6: // update password
				std::cout << "Enter application name: ";
				std::cin >> name;
				temp = root->findNode(name);
				std::cout << "Enter new password: ";
				std::cin >> password;
				temp->setPassword(password);
				break;
			case 7: // save as... and exit
				std::cout << "New file name: ";
				std::cin >> filename;
				std::cout << "New password: ";
				std::cin >> masterPassword;
				// FALLTHROUGH
			case 8: // save changes and exit
				root->saveToFile(filename, masterPassword); //throws runtime_error
				std::cout << "File saved" << std::endl;
				// FALLTHROUGH
			case 9: // discard changes and exit
				root = root->deleteAllNodes();
				return true;
			default:
				printEntriesMenu();
				std::cout << "Input not recognised, please try again" << std::endl;
			}
		}
		catch (std::runtime_error& re)
		{
			std::cerr << re.what() << std::endl;
		}
		catch (std::exception&)
		{
			std::cerr << "Could not save file '" + filename + "'" << std::endl;
		}
	}
}

/*
* Prints the start menu help message.
*/
void printstartMenu()
{
	std::cout << "1) Open an existing database" << std::endl
		<< "2) Create a new database" << std::endl
		<< "3) Quit application" << std::endl << std::endl;
}

/*
* Prints the entries menu help message.
*/
void printEntriesMenu()
{
	std::cout << "1) List all entries" << std::endl
		<< "2) Search for an entry" << std::endl
		<< "3) Add an entry" << std::endl
		<< "4) Delete an entry" << std::endl
		<< "5) Update username" << std::endl
		<< "6) Update password" << std::endl
		<< "7) Save As... and exit" << std::endl
		<< "8) Save and exit" << std::endl
		<< "9) Discard changes and exit" << std::endl << std::endl;
}