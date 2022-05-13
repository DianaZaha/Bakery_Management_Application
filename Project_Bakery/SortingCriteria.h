#pragma once
#include "Pastry.h"
#include "Repo.h"

/**
 * Class that manages the sorting options on a Repo.
 */
class SortingCriteria
{
private:
	Repo<Pastry> repo;/** copy of the elements from the Repo we want filtered in a ceratin way */
public:
	SortingCriteria(vector<Pastry>&);
	vector<Pastry> SortByName();
	vector<Pastry> SortByStock();
	vector<Pastry> SortByPrice();
	vector<Pastry> SortBySugar();
	vector<Pastry> SortByType();
};

