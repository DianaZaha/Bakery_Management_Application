#include "FilteringCriteria.h"
#include <iterator>
using std::back_inserter;

/** A constructor
 * .
 * Loads all the elements from the Repo into this Filter
 * \param vector the vector from where we are going to copy all our elements
 */

FilteringCriteria::FilteringCriteria(vector<Pastry>& vector)
{
	for (int i = 0; i < vector.size(); i++)
		repo.add(vector[i]);
}

/**
* Creates a vector with Pastries that have a certain name.
* \param _name , the name we search for
* \return vector with all the Pastry that match the name
*/
vector<Pastry> FilteringCriteria::FilterByName(std::string _name)
{
	vector<Pastry> rez;
	vector<Pastry> all = repo.get_all();
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [_name](const auto& x) {
		return (x.getName() == _name);
		});
	return rez;
}

/**
* Creates a vector with Pastries that have the stock lower then a certain amount.
* \param _stock , the amount we search for
* \return vector with all the Pastry that match the criteria
*/
vector<Pastry> FilteringCriteria::FilterByStock(int _stock)
{
	vector<Pastry> rez;
	vector<Pastry> all = repo.get_all();
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [_stock](const auto& x) {
		return (x.getStock() < _stock);
		});
	return rez;
}

/**
* Creates a vector with Pastries that have the price lower then a certain amount.
* \param _price , the amount we search for
* \return vector with all the Pastry that match the criteria
*/
vector<Pastry> FilteringCriteria::FilterByPrice(float _price)
{
	vector<Pastry> rez;
	vector<Pastry> all = repo.get_all();
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [&_price](const auto& x) {
		return _price > x.getPrice();
		});
	return rez;
}

/**
* Creates a vector with Pastries that have a stock lower then a certain amount.
* \param _stock , the amount we search for
* \return vector with all the Pastry that match the criteria
*/
vector<Pastry> FilteringCriteria::FilterBySugar(float _sugar)
{
	vector<Pastry> rez;
	vector<Pastry> all = repo.get_all();
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [&_sugar](const auto& x) {
		return x.getSugar() < _sugar;
		});
	return rez;
}

/**
* Creates a vector with Pastries that have a stock lower then a certain amount.
* \param _stock , the amount we search for
* \return vector with all the Pastry that match the criteria
*/
vector<Pastry> FilteringCriteria::FilterByType(PastryType _type)
{
	vector<Pastry> rez;
	vector<Pastry> all = repo.get_all();
	std::copy_if(all.begin(), all.end(), std::back_inserter(rez), [_type](const auto& x) {
		return (x.getType() == _type);
		});
	return rez;
}
