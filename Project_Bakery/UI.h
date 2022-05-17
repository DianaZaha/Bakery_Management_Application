
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
#include "Controller.h"

/**
 * Class that manages the User Interface in the Console.
 */
class UI
{
private:
	
	Controller C;
	Pastry readPastry(std::string&);

	//these do not need a undo/redo function
	static void printmenu();
	static void printsortmenu();
	static void printvector(const vector<Pastry>&);
	static void printfiltermenu();
	void filter();
	void sort();
public:
	UI();
	void displayMenu();
};