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
	vector<Pastry> Filtered;
	Filtered = Bakery.get_all();
	FilteringCriteria Filter(Filtered);
	printfiltermenu();
	char ch;
	cin >> ch;
	cout << "\n";
	if (ch == 'N' || ch == 'n')
	{
		string name;
		cout << "Introduce name: ";
		cin >> name;
		printvector(Filter.FilterByName(name));
	}
	if (ch == 'P' || ch == 'p')
	{
		float price;
		cout << "Introduce price: ";
		cin >> price;
		printvector(Filter.FilterByPrice(price));
	}
	if (ch == 'S' || ch == 's')
	{
		float sugar;
		cout << "Introduce sugar: ";
		cin >> sugar;
		printvector(Filter.FilterBySugar(sugar));
	}
	if (ch == 'K' || ch == 'k')
	{
		int stock;
		cout << "Introduce stock: ";
		cin >> stock;
		printvector(Filter.FilterByStock(stock));
	}
	if (ch == 'T' || ch == 't')
	{
		std:: string type;
		cout << "Introduce type: ";
		cin >> type;
		PastryType t = PastryType::sweet;
		if (type == "sweet")
			t = PastryType::sweet;
		if (type == "salty")
			t = PastryType::salty;
		if (type == "bread")
			t = PastryType::bread;
		printvector(Filter.FilterByType(t));
	}
}

/** Sorts the elements currently present in the CSV
 * .
 *  @note This doesn't affect the elements in the CSV
 */

void UI::sort()
{
	vector<Pastry> Sorted;
	Sorted = Bakery.get_all();
	SortingCriteria Sorting(Sorted);
	printsortmenu();
	char ch;
	cin >> ch;
	cout << "\n";
	if (ch == 'I' || ch == 'i')
	{
		printvector(Sorted);
	}
	if (ch == 'N' || ch == 'n')
	{
		printvector(Sorting.SortByName());
	}
	if (ch == 'K' || ch == 'k')
	{
		printvector(Sorting.SortByStock());
	}
	if (ch == 'P' || ch == 'p')
	{
		printvector(Sorting.SortByPrice());
	}
	if (ch == 'S' || ch == 's')
	{
		printvector(Sorting.SortBySugar());
	}
	if (ch == 'T' || ch == 't')
	{
		printvector(Sorting.SortByType());
	}
	
}

/**
 * The default constructor.
 * 
 */
UI::UI()
{
	Bakery = FileRepo<Pastry>("");
}

/**
 * A constructor.
 * 
 * Takes the filepath given and creates a FileRepo on which the UI will operate
 * @note The user can only modify the content from the CSV given only at add, delete, update, undo() and redo()
 * \param filepath the filepath to the CSV document that the UI operates on
 */
UI::UI(std::string filepath)
{
	Bakery = FileRepo<Pastry>(filepath);
}

/**
 * Calls the functions which perform the desired operation on FileRepo.
 * 
 * This function allows the user to input a character that will lead to an action being performed on the FileRepo
 * The user can add, delete, update, an element , these action can be reversed by using undo and redo
 * The user can sort and filter the elements but the data from the CSV file won't be changed
 */

void UI::displayMenu()
{
	stack<Action<Pastry>> Undo;
	stack<Action<Pastry>> Redo;
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
			
			add(Undo);
			Redo = stack<Action<Pastry>>();
			
		}
		if (ch == 'M' || ch == 'm')
		{
			
			update(Undo);
			Redo = stack<Action<Pastry>>();
		}
		if (ch == 'D' || ch == 'd')
		{
			
			del(Undo);
			Redo = stack<Action<Pastry>>();
			
		}
		if (ch == 'U' || ch == 'u')
		{
			if (Undo.empty())
				cout << "Sorry, you cannot undo anymore :(\n";
			else {
				Action<Pastry> current = Undo.top();
				Undo.pop();
				Redo.push(current);
				undo(current);
			}

		}
		if (ch == 'R' || ch == 'r')
		{
			if (Redo.empty())
				cout << "Sorry, you cannot redo anymore :(\n";
			else {
				Action<Pastry> current = Redo.top();
				Redo.pop();
				Undo.push(current);
				redo(current);
			}

		}
		if (ch == 'G' || ch == 'g')
		{
			vector<Pastry> All;
			All = Bakery.get_all();
			printvector(All);
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

/** Removes a Pastry from the FileRepo
 * .
 * It asks the user for an Id and creates a dummy Pastry with that it.
 * The dummy is passed to the remove function which only compares the Id's of the Pastries.
 * If the Pastry is not already there, it will warn the user.
 * Then we add to the top of the stack of Undo actions the actions it just performed.
 * \param Undo the stack of action previously taken by the user on he FileRepo
 */
void UI::del(stack<Action<Pastry>>& Undo)
{
	cout << "Which Pastry would you want to delete (only Id needed)\n";
	string s;
	cin >> s;
	Pastry Dummy(s, "", 0, 0.0, 0.0, PastryType::sweet);
	Pastry Old;
	try {
		Old = this->Bakery.search(Dummy);
		this->Bakery.remove(Dummy);
		}
	catch (const RepoException&)
	{
		cout << "This Pastry doesn't exist, you can add it^-^\n";
	}
	cout << "Change made succesfully!\n";
	Undo.push(Action<Pastry>(ActionType::deletion, Old, Dummy));
}

/**
 * Adds new pastry to the FileRepo
 * .
 * It reads a line from the user then creates a Pastry to match it.
 * It tries to add the Pastry in the FileRepo.
 * If the Pastry is already there, it will warn the user.
 * Then is adds to the top of the stack of Undo actions the actions it just performed,
 * 
 * \param Undo the stack of action previously taken by the user on the FileRepo
 */
void UI::add(stack<Action<Pastry>>& Undo)
{
	cout << "Introduce your new Pastry\n";
	std::string s;
	cin >> s;
	Pastry A;
	A = readPastry(s);
	try {
		this->Bakery.add(A);
	}
	catch (const RepoException&)
	{
	cout << "This Pastry already exist, you can update it ^-^\n";
	}
	cout << "Change made succesfully!\n";
	Pastry Dummy;
	Undo.push(Action<Pastry>(ActionType::addition, A, Dummy));
}

/** Updates a Pastry with new Stats
 * .
 * It read a line from the user and transforms it into a Pastry.
 * The Pastry that have been read must have the Id of one of the Pastry in the FileRepo.
 * If it doesn't exsit such a pastry, the user will be warned.
 * If the change have been made usccesfully, it adds the action and both the new and the old element to the Undo Stack.
 * \param Undo the stack of action previously taken by the user on he FileRepo
 */
void UI::update(stack<Action<Pastry>>& Undo)
{
	cout << "Introduce your modified Pastry\n";
	std::string s;
	cin >> s;
	Pastry A;
	A = readPastry(s);
	Pastry Old;
	try {
		Old = this->Bakery.search(A);
		this->Bakery.update(A);
	}
	catch (const RepoException&)
	{ 
		cout << "This Pastry doesn't exist, you can add it^-^\n";
	}
	Undo.push(Action<Pastry>(ActionType::addition, A, Old));
	cout << "Change made succesfully!\n";
}

/**
 * Used to undo an action.
 * 
 * To undo an action you have to do the oposite of the action given, accordingly to the indicated ActionType
 * \param Act the action that should be undone
 */
void UI::undo(Action<Pastry>& Act)
{
	ActionType Type = Act.getAction();
	Pastry Elem = Act.getElem();
	if (Type == ActionType::addition)
		this->Bakery.remove(Elem);
	if (Type == ActionType::deletion)
		this->Bakery.add(Elem);
	if (Type == ActionType::update)
		this->Bakery.update(Elem);
	cout << "Undo made succesfully!\n";
}

/**
 * Used to redo an action.
 *
 * To redo is just and undo of an undo, so we have to act accordingly to the indicated ActionType
 * \param Act the action that should be redone
 */
void UI::redo(Action<Pastry>& Act)
{
	ActionType Type = Act.getAction();
	Pastry Elem = Act.getElem();
	Pastry Old = Act.getElem1();
	if (Type == ActionType::addition)
		this->Bakery.add(Elem);
	if (Type == ActionType::deletion)
		this->Bakery.remove(Elem);	
	if (Type == ActionType::update)
		this->Bakery.update(Old);
	cout << "Redo made succesfully!\n";
}

