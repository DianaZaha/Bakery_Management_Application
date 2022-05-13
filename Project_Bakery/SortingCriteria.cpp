#include "SortingCriteria.h"

/** A constructor
 * .
 *	Loads all the elements from the Repo into this Filter
 * \param vector the vector from where we are going to copy all our elements
 */
SortingCriteria::SortingCriteria(vector<Pastry>& vector)
{
	for (int i = 0; i < vector.size(); i++)
		repo.add(vector[i]);
}

/**
 * Sorts the Repo in alphabetical order.
 * 
 * \return a sorted vector
 */
vector<Pastry> SortingCriteria::SortByName()
{
	vector<Pastry> all = repo.get_all();
	std::sort(all.begin(),all.end(), [](const auto& x, const auto& y) {
		return x.getName() < y.getName();
		});
	return all;
}

/**
 * Sorts the Repo in ascending order based on stock
 *
 * \return a sorted vector
 */
vector<Pastry> SortingCriteria::SortByStock()
{
	vector<Pastry> all = repo.get_all();
	std::sort(all.begin(), all.end(), [](const auto& x, const auto& y) {
		return x.getStock() < y.getStock();
		});
	return all;
}

/**
 * Sorts the Repo in ascending order based on price
 *
 * \return a sorted vector
 */
vector<Pastry> SortingCriteria::SortByPrice()
{
	
	vector<Pastry> all = repo.get_all();
	std::sort(all.begin(), all.end(), [](const auto& x, const auto& y) {
		return x.getPrice() < y.getPrice();
		});
	return all;
}

/**
 * Sorts the Repo in ascending order based on Sugar
 *
 * \return a sorted vector
 */
vector<Pastry> SortingCriteria::SortBySugar()
{
	vector<Pastry> all = repo.get_all();
	std::sort(all.begin(), all.end(), [](const auto& x, const auto& y) {
		return x.getSugar() < y.getSugar();
		});
	return all;
}

/**
 * Sorts the Repo in alpabethical order based on PastryType
 *
 * \return a sorted vector
 */

vector<Pastry> SortingCriteria::SortByType()
{
	vector<Pastry> all = repo.get_all();
	std::sort(all.begin(), all.end(), [](const auto& x, const auto& y) {
		return x.getType() < y.getType();
		});
	return all;
}
