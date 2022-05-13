#pragma once

#include "Pastry.h"
#include "Repo.h"

/**
 * Class that manages the filtering options on a Repo.
 */
class FilteringCriteria
{
private:
	Repo<Pastry> repo;/** the basically a copy of the elements from the Repo we want filtered in a ceratin way */ 
public:
	FilteringCriteria(vector<Pastry>&);
	vector<Pastry> FilterByName(std::string);
	vector<Pastry> FilterByStock(int);
	vector<Pastry> FilterByPrice(float);
	vector<Pastry> FilterBySugar(float);
	vector<Pastry> FilterByType(PastryType);
};




