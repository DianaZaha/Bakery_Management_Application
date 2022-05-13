#pragma once

#include <string>
#include<iostream>
using std::string;
using std::istream;
using std::ostream;

/**
 * This Class Tells us what kind of Pastry we have
 */
enum class PastryType{

	bread = 0, /**<  used for a pastry with low amount of sugar, which can categorize as bread acoording to their sugar*/
	salty = 1, /**< used for a pastry which has a salty taste, usually with a lower amount of sugar, and a salty ingredients */
	sweet = 2, /**< used for a pastry which has a sweet taste, usually with a very high amount of sugar */
};

/**
 * Class that manages the atributes of a real life pastry.
 */
class Pastry
{
private:
	std::string id; /** id of the current pastry */ 
	std::string name; /** comercial name of the pastry */
	int stock;  /**  number of pastries available at the store */
	float price;  /**  comercial price of the pastry*/
	float sugar; /**  grams of sugar from the total composition */
	PastryType type; /** type of pastry we are having */

public:
	Pastry();
	Pastry(string, string, int, float, float, PastryType);

	Pastry(const Pastry&);
	Pastry& operator=(const Pastry&);

	std::string getId() const;
	std::string getName() const;
	int getStock() const;
	float getPrice() const;
	float getSugar() const;
	PastryType getType() const;

	void setName(const std::string);
	void setStock(int);
	void setPrice(float);
	void setSugar(float);

	friend ostream& operator<<(ostream&, const Pastry&);
	friend istream& operator>>(istream&, Pastry&);

	friend bool operator==(const Pastry&, const Pastry&);
	friend bool operator<(const Pastry&, const Pastry&);
	friend bool operator>(const Pastry&, const Pastry&);

	~Pastry();
};

