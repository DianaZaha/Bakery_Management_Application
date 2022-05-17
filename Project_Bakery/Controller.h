#pragma once
#include <string>
#include <stack>

using std::stack;

#include "Pastry.h"
#include "FileRepo.h"
#include "Repo.h"
#include "Action.h"
#include "FilteringCriteria.h"
#include "SortingCriteria.h"


class Controller
{
private:
	std::string filepath;
	FileRepo<Pastry> Bakery;
	stack<Action<Pastry>> Undo;
	stack<Action<Pastry>> Redo;

public:
	Controller();
	Controller(std::string);

	//these need a undo/redo function
	void add(Pastry);
	void del(Pastry);
	void update(Pastry);

	void undo();
	void redo();

	vector<Pastry> FilterByName(std::string);
	vector<Pastry> FilterByStock(int);
	vector<Pastry> FilterByPrice(float);
	vector<Pastry> FilterBySugar(float);
	vector<Pastry> FilterByType(std::string);

	vector<Pastry> SortByName();
	vector<Pastry> SortByStock();
	vector<Pastry> SortByPrice();
	vector<Pastry> SortBySugar();
	vector<Pastry> SortByType();

	vector<Pastry> GetContent();

};

