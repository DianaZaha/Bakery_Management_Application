#include "Tests.h"
#include <cassert>

/**
 * Performs the tests on class Pastry and Action
 * 
 */
void Tests::TestDomain()
{
	Pastry A;
	assert(A.getId() == "");
	assert(A.getName() == "");
	assert(A.getStock() == 0);
	assert(fabs(A.getPrice() - 0.0) < 0.001);
	assert(fabs(A.getSugar() - 0.0) < 0.001);
	assert(A.getType() == PastryType::sweet);

	Pastry A1{ "1","Cinnamon Bun", (int)100, (float)5.9, (float)230, PastryType::sweet };
	Pastry A2{ "2","Cheese Croisant", (int)130, (float)14.7, (float)150, PastryType::salty};

	assert(A2.getId() == "2");
	assert(A2.getName() == "Cheese Croisant");
	assert(A2.getStock() == 130);
	assert(fabs(A2.getPrice() - 14.7) < 0.001);
	assert(A2.getType() == PastryType::salty);

	A = A1;
	assert(A == A1);

	Pastry A3(A1);
	assert(A3.getName() == A1.getName());
	assert(A3.getName() == "Cinnamon Bun");
	A2 = A3;
	assert(A3.getName() == A2.getName());

	Pastry A4{ "3","Struddle",(int)50, (float) 12.80, (float) 334.5, PastryType::sweet };
	assert((A1 < A4) == true);
	assert((A1 > A4) == false);
}

/**
 * Performs the tests on Classes FilteringCriteria and SortingCriteria.
 * 
 */
void Tests::TestFilteringandSorting()
{
}

/**
 * Performs the tests on Repo and FileRepo.
 * 
 */

void Tests::TestRepo()
{
}

/**
 * Starts the tests.
 * 
 */
void Tests::TestAll()
{
	this->TestDomain();
	this->TestFilteringandSorting();
	this->TestRepo();
}
