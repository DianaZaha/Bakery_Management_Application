
#pragma once
#include <iostream>
#include <string>
#include <stack>

using std::stack;

#include "FileRepo.h"
#include "Repo.h"
#include "Pastry.h"
#include "Action.h"
#include "FilteringCriteria.h"
#include "SortingCriteria.h"

/**
 * Class that manages the User Interface in the Console.
 */
class UI
{
private:

	FileRepo<Pastry> Bakery; /** The FileRepo that this UI allows the user to perform operations on */ 
	
	Pastry readPastry(std::string&);

	//these do not need a undo/redo function
	static void printmenu();
	static void printsortmenu();
	static void printvector(const vector<Pastry>&);
	static void printfiltermenu();
	void filter();
	void sort();

	//these need a undo/redo function
	void del(stack<Action<Pastry>>&);
	void add(stack<Action<Pastry>>&);
	void update(stack<Action<Pastry>>&);
	void undo(Action<Pastry>&);
	void redo(Action<Pastry>&);
public:
	UI();
	UI(std::string);
	void displayMenu();
};