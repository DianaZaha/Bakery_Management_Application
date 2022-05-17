#include "UI.h"
#include <stack>
#include <cassert>
#include <vector>
#include <iterator>
#include <iostream>
#include <string>

#include "Repo.h"

using std::cout;
using std::cin;
using std::stack;
using std::stringstream;
#include <sstream>

/** Used to tranform a string into a vector a strings
 * .
 * The functions creates a new string everytime it meets the delimiter with the content in between 2 delimiters,
 * adding the newly formed string to the vector of strings
 * \param str the string that should be broken off
 * \param delimiter the character at which the string is broken off
 * \return a vector of strings
 */
vector<string> tokenize2(string str, char delimiter)
{
	vector <string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

/**
 * Creates from a line a Pastry.
 * 
 * \param line the line readen from keyboard
 * \return The newly formed Pastry
 */
Pastry UI::readPastry(std::string &line)
{
	vector<string> tokens = tokenize2(line, ',');
	if (tokens.size() != 6) // make sure the data we have is ok
		cout << "please respect the Pastry format :)\n";

	string id;
	id = tokens[0];
	string name;
	name = tokens[1];
	int stock = 0;
	std::istringstream(tokens[2]) >> stock;
	float price = 0.0;
	std::istringstream(tokens[3]) >> price;
	float sugar = 0.0;
	std::istringstream(tokens[4]) >> sugar;
	std::string s;
	PastryType t = PastryType::sweet;
	std::istringstream(tokens[5]) >> s;
	if (s == "sweet")
		t = PastryType::sweet;
	if (s == "salty")
		t = PastryType::salty;
	if (s == "bread")
		t = PastryType::bread;
	Pastry A(id, name, stock, price, sugar, t);

	return A;
}

/**
 * Shows the Main Menu to the user.
 * 
 */
void UI::printmenu()
{
	cout << "Please select your option\n\t";
	cout << "A|a\tAdd a Pastry\n\t";
	cout << "M|m\tUpdate a Pastry\n\t";
	cout << "D|d\tDelete a Pastry\n\n\t";
	cout << "U|u\tUndo\t\tR|r\tRedo\n\n\t";
	cout << "G|g\tShow all Pastries\n\t";
	cout << "F|f\tFilter Pastries\n\t";
	cout << "S|s\tSort Pastries\n\t";

	cout << "Q|q\tquit\n";
}

/**
 * Shows the Sorting Menu to the user.
 *
 */
void UI::printsortmenu()
{
	cout << "!Please note that this sort won't affect the data in the file!\n";
	cout << "How would you like to sort the Pastries\n\t";
	cout << "I|i\t Sort after Id\n\t";
	cout << "N|n\t Sort after Name\n\t";
	cout << "K|k\t Sort after Stock\n\t";
	cout << "P|p\t Sort after Price\n\t";
	cout << "S|s\t Sort after Sugar\n\t";
	cout << "T|t\t Sort by Type\n\t";
	cout << "Your option: ";
}

/**
 * Prints all the elemets from the vector in the console.
 * 
 * \param vector the vector whose elements we want to print in the console
 */

void UI::printvector(const vector<Pastry>& vector)
{
	cout << "ID,Name,Stock,Price,Sugar,Type\n";
	for (auto element : vector) {
		cout << element << "\n";
	}
}

/**
 * Shows the Filtering Menu to the user.
 *
 */
void UI::printfiltermenu()
{
	cout << "!Please note that this filter won't affect the data in the file!\n";
	cout << "How would you like to filter the Pastries\n\t";
	cout << "N|n\t Filter By Name\n\t";
	cout << "T|t\t Filter by Type\n\t";
	cout << "K|k\t Filter By Stock (less than)\n\t";
	cout << "P|p\t Filter By Price (less than)\n\t";
	cout << "S|s\t Filter By Sugar (less than)\n\t";
	cout << "Your option: ";
}

/** Filters the elements currently present in the CSV
 * .
 *  @note This doesn't affect the elements in the CSV
 */
void UI::filter()
{
	printfiltermenu();
	char ch;
	cin >> ch;
	cout << "\n";
	if (ch == 'N' || ch == 'n')
	{
		string name;
		cout << "Introduce name: ";
		cin >> name;
		printvector(C.FilterByName(name));
	}
	if (ch == 'P' || ch == 'p')
	{
		float price;
		cout << "Introduce price: ";
		cin >> price;
		printvector(C.FilterByPrice(price));
	}
	if (ch == 'S' || ch == 's')
	{
		float sugar;
		cout << "Introduce sugar: ";
		cin >> sugar;
		printvector(C.FilterBySugar(sugar));
	}
	if (ch == 'K' || ch == 'k')
	{
		int stock;
		cout << "Introduce stock: ";
		cin >> stock;
		printvector(C.FilterByStock(stock));
	}
	if (ch == 'T' || ch == 't')
	{
		std:: string type;
		cout << "Introduce type: ";
		cin >> type;
		printvector(C.FilterByType(type));
	}
}

/** Sorts the elements currently present in the CSV
 * .
 *  @note This doesn't affect the elements in the CSV
 */

void UI::sort()
{
	printsortmenu();
	char ch;
	cin >> ch;
	cout << "\n";
	if (ch == 'I' || ch == 'i')
	{
		printvector(C.GetContent());
	}
	if (ch == 'N' || ch == 'n')
	{
		printvector(C.SortByName());
	}
	if (ch == 'K' || ch == 'k')
	{
		printvector(C.SortByStock());
	}
	if (ch == 'P' || ch == 'p')
	{
		printvector(C.SortByPrice());
	}
	if (ch == 'S' || ch == 's')
	{
		printvector(C.SortBySugar());
	}
	if (ch == 'T' || ch == 't')
	{
		printvector(C.SortByType());
	}
}

/**
 * The default constructor.
 * 
 */
UI::UI()
{
	C = Controller("BakeryInfo.csv");
}

void UI::displayMenu()
{
	int x = 1;
	char ch;
	while (x)
	{
		printmenu();
		cout << "Your option: ";
		cin >> ch;
		cout << "\n";
		if (ch == 'A' || ch == 'a')
		{
			
			cout << "Introduce your new Pastry\n";
			std::string s;
			cin >> s;
			Pastry A;
			A = readPastry(s);
			try {
				C.add(A);
			}
			catch (const RepoException&)
			{
				cout << "This Pastry already exist, you can update it ^-^\n";
			}
			cout << "Change made succesfully!\n";
			
		}
		if (ch == 'M' || ch == 'm')
		{
			
			cout << "Introduce your modified Pastry\n";
			std::string s;
			cin >> s;
			Pastry A;
			A = readPastry(s);
			try {
				C.update(A);
			}
			catch (const RepoException&)
			{
				cout << "This Pastry doesn't exist, you can add it^-^\n";
			}
			cout << "Change made succesfully!\n";
		}
		if (ch == 'D' || ch == 'd')
		{
			
			cout << "Which Pastry would you want to delete (only Id needed)\n";
			string s;
			cin >> s;
			
			try {
				C.del(Pastry(s, "", 0, 0.0, 0.0, PastryType::sweet));
			}
			catch (const RepoException&)
			{
				cout << "This Pastry doesn't exist, you can add it^-^\n";
			}
			cout << "Change made succesfully!\n";
			
		}
		if (ch == 'U' || ch == 'u')
		{
			
			try {
				C.undo();
			}
			catch (const RepoException&)
			{
				cout << "You cannot undo anymore\n";
			}
			cout << "Undo made succesfully!\n";

		}
		if (ch == 'R' || ch == 'r')
		{
			try {
				C.redo();
			}
			catch (const RepoException&)
			{
				cout << "You cannot undo anymore\n";
			}
			cout << "Undo made succesfully!\n";

		}
		if (ch == 'G' || ch == 'g')
		{
			printvector(C.GetContent());
		}
		if (ch == 'F' || ch == 'f')
			filter();
		if (ch == 'S' || ch == 's')
			sort();
		if(ch == 'Q' || ch == 'q')
			x = 0;
		cout << "\n";
	}
	
}