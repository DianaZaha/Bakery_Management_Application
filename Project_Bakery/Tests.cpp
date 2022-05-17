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

	Pastry C;
	C.setName("bla");
	assert(C.getName() == "bla");
	C.setPrice(7000.5);
	assert(fabs(C.getPrice() - 7000.5) < 0.001);
	C.setStock(400);
	assert(C.getStock() == 400);
	C.setSugar(700.90);
	assert(fabs(C.getSugar() - 700.90) < 0.001);

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

	Action<Pastry> Act;
	assert(Act.getAction() == ActionType::addition);

	Action<Pastry> B(ActionType::update, A1, A4);
	assert(B.getAction() == ActionType::update);
	assert(B.getElem() == A1);
	assert(B.getElem1() == A4);

}

/**
 * Performs the tests on Classes FilteringCriteria and SortingCriteria.
 * 
 */
void Tests::TestFilteringandSorting()
{
	Repo<Pastry> Rep;
	assert(Rep.size() == 0);

	Pastry A1{ "1","Cinnamon Bun", (int)50, (float)5.9, (float)30, PastryType::sweet };
	Pastry A2{ "2","Struddle", (int)130, (float)14.7, (float)150, PastryType::salty };
	Pastry A3{ "3","Cheese Croisant",(int)100, (float)12.80, (float)134.5, PastryType::sweet };
	Rep.add(A1);
	Rep.add(A2);
	Rep.add(A3);

	vector<Pastry> Filtered;
	Filtered = Rep.get_all();
	FilteringCriteria F(Filtered);

	Repo<Pastry> Try;
	Try.add(A2);

	assert(Try.size() == F.FilterByName("Struddle").size());
	Try.remove(A2);

	Try.add(A1);
	assert(Try.size() == F.FilterByStock(60).size());
	assert(Try.size() == F.FilterByPrice(7.0).size());
	assert(Try.size() == F.FilterBySugar(40).size());
	Try.add(A3);
	assert(Try.size() == F.FilterByType(PastryType::sweet).size());
	Try.remove(A3);
	Try.remove(A1);
	
	vector<Pastry> Sorted;
	Sorted = Rep.get_all();
	SortingCriteria S(Sorted);

	Try.add(A1);
	Try.add(A3);
	Try.add(A2);

	assert(Try.size() == S.SortByName().size());
	assert(Try.size() == S.SortByStock().size());
	assert(Try.size() == S.SortByPrice().size());
	assert(Try.size() == S.SortBySugar().size());

	Try.remove(A3);
	Try.remove(A1);
	Try.add(A1);
	Try.add(A3);
	assert(Try.get_all().size() == S.SortByType().size());

}

/**
 * Performs the tests on Repo and FileRepo.
 * 
 */

void Tests::TestRepo()
{
	FileRepo<Pastry> Rep("teste.csv");
	
	assert(Rep.size() == 0);

	Pastry A1{ "1","Cinnamon Bun", (int)100, (float)5.9, (float)230, PastryType::sweet };
	Pastry A2{ "2","Cheese Croisant", (int)130, (float)14.7, (float)150, PastryType::salty };
	Rep.add(A1);
	assert(Rep.size() == 1);
	Rep.add(A2);
	assert(Rep.size() == 2);

	Pastry F = Rep.search(A1);
	assert(F == A1);

	try {
		Rep.add(A1);
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "existent element!\n");
	}

	Pastry A3{ "3","Struddle",(int)50, (float)12.80, (float)334.5, PastryType::sweet };

	try {
		Rep.search(A3);
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "inexistent element!\n");
	}

	try {
		Rep.remove(A3);
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "inexistent element!\n");
	}

	try {
		Rep.update(A3);
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "inexistent element!\n");
	}

	Pastry A21{ "2","Caramel",(int)50, (float)12.80, (float)334.5, PastryType::sweet };

	Rep.update(A21);
	assert(Rep.search(A21).getName() == "Caramel");

	Rep.remove(A1);
	Rep.remove(A2);
}

/**
 * Performs the tests on the Controller
 *
 */
void Tests::TestController()
{
	Controller C("teste.csv");

	assert(C.GetContent().size() == 0);

	Pastry A1{ "1","Cinnamon Bun", (int)100, (float)5.9, (float)230, PastryType::sweet };
	Pastry A2{ "2","Cheese Croisant", (int)130, (float)14.7, (float)150, PastryType::salty };
	C.add(A1);
	assert(C.GetContent().size() == 1);
	C.add(A2);
	assert(C.GetContent().size() == 2);

	try {
		C.add(A1);
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "existent element!\n");
	}

	C.undo();
	try {
		C.undo();
	}catch (const RepoException& re)
	{
		assert(re.get_message() == "Empty Undo stack!\n");
	}

	C.redo();
	try {
		C.redo();
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "Empty Redo stack!\n");
	}

	try {
		C.add(A1);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "existent element!\n");
	}

	Pastry A3{ "3","Struddle",(int)50, (float)12.80, (float)334.5, PastryType::sweet };

	try {
		C.del(A3);
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "inexistent element!\n");
	}

	C.undo();
	try {
		C.undo();
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "Empty Undo stack!\n");
	}

	C.redo();
	try {
		C.redo();
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "Empty Redo stack!\n");
	}

	try {
		C.del(A3);
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "inexistent element!\n");
	}

	try {
		C.update(A3);
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "inexistent element!\n");
	}

	C.undo();
	try {
		C.undo();
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "Empty Undo stack!\n");
	}

	C.redo();
	try {
		C.redo();
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "Empty Redo stack!\n");
	}

	try {
		C.update(A3);
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.get_message() == "inexistent element!\n");
	}

	Pastry A21{ "2","Caramel",(int)50, (float)12.80, (float)334.5, PastryType::sweet };

	C.update(A21);

	C.del(A1);
	C.del(A2);

	assert(C.GetContent().size() == 0);

	Pastry B1{ "1","Cinnamon Bun", (int)50, (float)5.9, (float)30, PastryType::sweet };
	Pastry B2{ "2","Struddle", (int)130, (float)14.7, (float)150, PastryType::salty };
	Pastry B3{ "3","Cheese Croisant",(int)100, (float)12.80, (float)134.5, PastryType::sweet };
	C.add(B1);
	C.add(B2);
	C.add(B3);

	vector<Pastry> Try;
	Try.push_back(B2);

	assert(Try.size() == C.FilterByName("Struddle").size());
	auto it = std::find(Try.begin(),Try.end(), B2);
	Try.erase(it);

	Try.push_back(B1);
	assert(Try.size() == C.FilterByStock(60).size());
	assert(Try.size() == C.FilterByPrice(7.0).size());
	assert(Try.size() == C.FilterBySugar(40).size());
	Try.push_back(B3);
	assert(Try.size() == C.FilterByType("sweet").size());
	it = std::find(Try.begin(), Try.end(), B3);
	Try.erase(it);
	it = std::find(Try.begin(), Try.end(), B1);
	Try.erase(it);

	Try.push_back(B1);
	Try.push_back(B3);
	Try.push_back(B2);

	assert(Try.size() == C.SortByName().size());
	assert(Try.size() == C.SortByStock().size());
	assert(Try.size() == C.SortByPrice().size());
	assert(Try.size() == C.SortBySugar().size());

	it = std::find(Try.begin(), Try.end(), B3);
	Try.erase(it);
	it = std::find(Try.begin(), Try.end(), B1);
	Try.erase(it);
	Try.push_back(B1);
	Try.push_back(B3);
	assert(Try.size() == C.SortByType().size());

	C.del(B1);
	C.del(B2);
	C.del(B3);
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
	this->TestController();
}
