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
			startMenu(false, mode::MENU, "");
			break;
		case 3: // arguments passed
			if (strcmp(argv[1], "-n") == 0) // create a new file
			{
				startMenu(true, mode::NEW, std::string(argv[2]));
			}
			else if (strcmp(argv[1], "-o") == 0) // opena a file
			{
				startMenu(true, mode::OPEN, std::string(argv[2]));
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
	std::string filename;
	std::string masterPassword;
	AVLTree* root = nullptr;
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
				choice = mode::MENU;
			}
		}
		switch (choice)
		{
		case mode::OPEN: // Open an existing database
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
				entriesMenu(root, filename, masterPassword);
			}
			catch (std::runtime_error& re)
			{
				std::cerr << re.what() << std::endl;
				choice = mode::MENU;
			}
			catch (std::exception&)
			{
				std::cerr << "Could not open file '" + filename + "'" << std::endl;
				if (argsPassed) break;
				choice = mode::MENU;
			}
			break;
		case mode::NEW: // Create a new database
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
			entriesMenu(root, filename, masterPassword);
			// FALLTHROUGH
		case mode::QUIT:
			// Quitting application
			break;
		default:
			printstartMenu();
			std::cout << "Input not recognised, please try again" << std::endl;
			choice = mode::MENU;
			break;
		}
	} while (choice == mode::MENU);

	std::cout << "Quitting application..." << std::endl;
}

/*
* Provides the menu used for managing entries in the database.
*/
void entriesMenu(AVLTree* root, std::string& filename, std::string& masterPassword)
{
	printEntriesMenu();

	while (true)
	{
		try {
			int choice = command::ASK;
			std::string name;
			std::string username;
			std::string password;
			AVLTree* temp;
			std::cout << " > ";
			std::cin >> choice;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				choice = command::ASK;
			}
			switch (choice)
			{
			case command::LIST_ALL: // List all entries
				std::cout << root->allToString();
				break;
			case command::FIND: // find an entry
				std::cout << "Enter application name to search: ";
				std::cin >> name;
				std::cout << root->findNode(name)->toString();
				break;
			case command::ADD: // add an entry
				std::cout << "Enter application name: ";
				std::cin >> name;
				std::cout << "Enter username: ";
				std::cin >> username;
				std::cout << "Enter password: ";
				std::cin >> password;
				root = root->insertNodeAVL(name, username, password); //throws runtime_error
				break;
			case command::DELETE: // delete an entry
				std::cout << "Application name to delete: ";
				std::cin >> name;
				root = root->deleteNode(name); //balance
				break;
			case command::UPDATE_USERNAME: // update username
				std::cout << "Enter application name: ";
				std::cin >> name;
				temp = root->findNode(name);
				std::cout << "Enter new username: ";
				std::cin >> username;
				temp->setUsername(username);
				break;
			case command::UPDATE_PASSWORD: // update password
				std::cout << "Enter application name: ";
				std::cin >> name;
				temp = root->findNode(name);
				std::cout << "Enter new password: ";
				std::cin >> password;
				temp->setPassword(password);
				break;
			case command::SAVE_AS: // save as... and exit
				std::cout << "New file name: ";
				std::cin >> filename;
				std::cout << "New password: ";
				std::cin >> masterPassword;
				// FALLTHROUGH
			case command::SAVE: // save changes and exit
				root->saveToFile(filename, masterPassword); //throws runtime_error
				std::cout << "File saved" << std::endl;
				// FALLTHROUGH
			case command::EXIT: // discard changes and exit
				root = root->deleteAllNodes();
				return;
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