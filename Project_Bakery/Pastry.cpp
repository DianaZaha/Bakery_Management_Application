#include "Pastry.h"
#include <vector>

using std::vector;
using std::stringstream;
#include <sstream>

/** A constructor.
 * 
 * The default constructor.
 */
Pastry::Pastry()
{
	id = "";
	name = "";
	stock = 0;
	price = 0.0;
	sugar = 0.0;
	type = PastryType::sweet;
}

/** A constructor.
 * .
 * Creates a Pastry with the paramters given
 * \param _id id of the current pastry
 * \param _name comercial name of the pastry
 * \param _stock number of pastries available at the store
 * \param _price comercial price of the pastry
 * \param _sugar grams of sugar from the total compositio
 * \param _type type of pastry we are having
 */
Pastry::Pastry(string _id, string _name, int _stock, float _price, float _sugar, PastryType _type) :
	id{ _id }, name{ _name }, stock{ _stock }, price{ _price }, sugar{ _sugar }, type{ _type }
{
}

/** Copy constructor (Rule of 3).
 * Used to create a pastry similar to the given one
 * \param other A pastry that should be copied
 */
Pastry::Pastry(const Pastry& other)
{
	id = other.id;
	name = other.name;
	stock = other.stock;
	price = other.price;
	sugar = other.sugar;
	type = other.type;
}

/** Copy assignment operator (Rule of 3).
 * Here we overriden the asigment operator
 * \param other A pastry that should be copied
 * \return the newly formed pastry
 */
Pastry& Pastry::operator=(const Pastry& other)
{
	id = other.id;
	name = other.name;
	stock = other.stock;
	price = other.price;
	sugar = other.sugar;
	type = other.type;
	return *this;
}

/**
 * .
 * 
 * \return the id of the pastry
 */
std::string Pastry::getId() const
{
	return id;
}

/**
 * .
 *
 * \return the comercial name of the pastry
 */
std::string Pastry::getName() const
{
	return name;
}

/**
 * .
 *
 * \return the current available stock of the pastry
 */
int Pastry::getStock() const
{
	return stock;
}

/**
 * .
 * 
 * \return the comercial price of the pastry
 */
float Pastry::getPrice() const
{
	return price;
}

/**
 * .
 * 
 * \return the amount of sugar in the current pastry
 */
float Pastry::getSugar() const
{
	return sugar;
}

/**
 * .
 * 
 * \return the type of pastry according to PastryType enum class
 */
PastryType Pastry::getType() const
{
	return type;
}

/**
 * .
 * 
 * \param other the new name of the pastry
 */
void Pastry::setName(const std::string other)
{
	name = other;
}

/**
 * .
 * 
 * \param other the new available stock of the pastry
 */
void Pastry::setStock(int other)
{
	stock = other;
}

/**
 * .
 * 
 * \param other the new comercial price of the pastry
 */
void Pastry::setPrice(float other)
{
	price = other;
}

/**
 * .
 * 
 * \param other the new amount of sugar in pastry
 */
void Pastry::setSugar(float other)
{
	sugar = other;
}

/**
 * A default constructor.
 * 
 */
Pastry::~Pastry()
{
}

/** Overriden the output operator
 * .
 * 
 * \param os ostrem
 * \param pastry curent pastry
 * \return ostream
 */
ostream& operator<<(ostream& os, const Pastry& pastry)
{
	os << pastry.id <<"," << pastry.name << "," << pastry.stock << "," << pastry.price << "," << pastry.sugar << ",";
	if (pastry.type == PastryType::sweet)
		os << "sweet";
	if (pastry.type == PastryType::salty)
		os << "salty";
	if (pastry.type == PastryType::bread)
		os << "bread";
	return os;
}

/** Used to tranform a string into a vector a strings
 * .
 * The functions creates a new string everytime it meets the delimiter with the content in between 2 delimiters, 
 * adding the newly formed string to the vector of strings
 * \param str the string that should be broken off
 * \param delimiter the character at which the string is broken off
 * \return a vector of strings
 */

vector<string> tokenize(string str, char delimiter)
{
	vector <string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}


/** Overriden the input operator
 * .
 * 
 * \param is istream
 * \param pastry The pastry that is curently inputed
 * \return is istream
 */
istream& operator>>(istream& is, Pastry& pastry)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 6) // make sure the data we have is ok
		return is;

	pastry.id = tokens[0];
	pastry.name = tokens[1];
	int stock = 0;
	std::istringstream(tokens[2]) >> stock;
	pastry.stock = stock;
	float price = 0.0;
	std::istringstream(tokens[3]) >> price;
	pastry.price = price;
	float sugar = 0.0;
	std::istringstream(tokens[4]) >> sugar;
	pastry.sugar = sugar;
	std::string s;
	std::istringstream(tokens[5]) >> s;
	if (s == "sweet")
		pastry.type = PastryType::sweet;
	if (s == "salty")
		pastry.type = PastryType::salty;
	if (s == "bread")
		 pastry.type = PastryType::bread;
	return is;
}

/** Overriden the equality operator
 * .
 * 
 * \param Pastry1 
 * \param Pastry2
 * \return true or false
 */

bool operator==(const Pastry& Pastry1, const Pastry& Pastry2)
{
	return (Pastry1.id == Pastry2.id);
}

/** Overriden the < operator
 * .
 * The function compares the 2 pastries soly based on their id
 * \param Pastry1
 * \param Pastry2
 * \return true or false
 */
bool operator<(const Pastry& Pastry1, const Pastry& Pastry2)
{
	return (Pastry1.id < Pastry2.id);
}

/** Overriden the < operator
 * .
 * The function compares the 2 pastries soly based on their id
 * \param Pastry1
 * \param Pastry2
 * \return true or false
 */
bool operator>(const Pastry& Pastry1, const Pastry& Pastry2)
{
	return (Pastry1.id > Pastry2.id);
}
