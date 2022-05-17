#include "Controller.h"
/**
 * The default constructor.
 *
 */
Controller::Controller()
{
	Bakery = FileRepo<Pastry>("BakeryInfo.csv");
}

/**
 * Calls the functions which perform the desired operation on FileRepo.
 *
 * This function allows the user to input a character that will lead to an action being performed on the FileRepo
 * The user can add, delete, update, an element , these action can be reversed by using undo and redo
 * The user can sort and filter the elements but the data from the CSV file won't be changed
 */
Controller::Controller(std::string s)
{
	Bakery = FileRepo<Pastry>(s);
}

/**
 * Adds new pastry to the FileRepo
 * .
 * It reads a line from the user then creates a Pastry to match it.
 * It tries to add the Pastry in the FileRepo.
 * If the Pastry is already there, it will warn the user.
 * Then is adds to the top of the stack of Undo actions the actions it just performed,
 *
 * \param Undo the stack of action previously taken by the user on the FileRepo
 */
void Controller::add(Pastry A)
{
	Bakery.add(A);
	Pastry Dummy;
	Redo = stack<Action<Pastry>>();
	Undo.push(Action<Pastry>(ActionType::addition, A, Dummy));
}

/** Removes a Pastry from the FileRepo
 * .
 * It asks the user for an Id and creates a dummy Pastry with that it.
 * The dummy is passed to the remove function which only compares the Id's of the Pastries.
 * If the Pastry is not already there, it will warn the user.
 * Then we add to the top of the stack of Undo actions the actions it just performed.
 * \param Undo the stack of action previously taken by the user on he FileRepo
 */
void Controller::del(Pastry A)
{
	
	Pastry Old;
	Old = this->Bakery.search(A);
	this->Bakery.remove(A);
	Redo = stack<Action<Pastry>>();
	Undo.push(Action<Pastry>(ActionType::deletion, Old, A));
}
/** Updates a Pastry with new Stats
 * .
 * It read a line from the user and transforms it into a Pastry.
 * The Pastry that have been read must have the Id of one of the Pastry in the FileRepo.
 * If it doesn't exsit such a pastry, the user will be warned.
 * If the change have been made usccesfully, it adds the action and both the new and the old element to the Undo Stack.
 * \param Undo the stack of action previously taken by the user on he FileRepo
 */
void Controller::update(Pastry A)
{
	Pastry Old;
	Old = this->Bakery.search(A);
	this->Bakery.update(A);
	Redo = stack<Action<Pastry>>();
	Undo.push(Action<Pastry>(ActionType::addition, A, Old));
}

/**
 * Used to undo an action.
 *
 * To undo an action you have to do the oposite of the action given, accordingly to the indicated ActionType
 * \param Act the action that should be undone
 */
void Controller::undo()
{
	if (Undo.empty())
		throw RepoException("Empty Undo stack!\n");
	Action<Pastry> Act = Undo.top();
	Undo.pop();
	Redo.push(Act);
	ActionType Type = Act.getAction();
	Pastry Elem = Act.getElem();
	if (Type == ActionType::addition)
		this->Bakery.remove(Elem);
	if (Type == ActionType::deletion)
		this->Bakery.add(Elem);
	if (Type == ActionType::update)
		this->Bakery.update(Elem);
}

/**
 * Used to redo an action.
 *
 * To redo is just and undo of an undo, so we have to act accordingly to the indicated ActionType
 * \param Act the action that should be redone
 */
void Controller::redo()
{
	if (Redo.empty())
		throw RepoException("Empty Redo stack!\n");
	Action<Pastry> Act = Redo.top();
	Redo.pop();
	Undo.push(Act);
	ActionType Type = Act.getAction();
	Pastry Elem = Act.getElem();
	Pastry Old = Act.getElem1();
	if (Type == ActionType::addition)
		this->Bakery.add(Elem);
	if (Type == ActionType::deletion)
		this->Bakery.remove(Elem);
	if (Type == ActionType::update)
		this->Bakery.update(Old);
}

vector<Pastry> Controller::FilterByName(std::string name)
{
	vector<Pastry> Filtered;
	Filtered = Bakery.get_all();
	FilteringCriteria Filter(Filtered);
	return Filter.FilterByName(name);;
}

vector<Pastry> Controller::FilterByStock(int stock)
{
	vector<Pastry> Filtered;
	Filtered = Bakery.get_all();
	FilteringCriteria Filter(Filtered);
	return Filter.FilterByStock(stock);;
}

vector<Pastry> Controller::FilterByPrice(float price)
{
	vector<Pastry> Filtered;
	Filtered = Bakery.get_all();
	FilteringCriteria Filter(Filtered);
	return Filter.FilterByPrice(price);;
}

vector<Pastry> Controller::FilterBySugar(float sugar)
{
	vector<Pastry> Filtered;
	Filtered = Bakery.get_all();
	FilteringCriteria Filter(Filtered);
	return Filter.FilterBySugar(sugar);
}

vector<Pastry> Controller::FilterByType(std::string type)
{
	vector<Pastry> Filtered;
	Filtered = Bakery.get_all();
	FilteringCriteria Filter(Filtered);
	PastryType t = PastryType::sweet;
	if (type == "sweet")
		t = PastryType::sweet;
	if (type == "salty")
		t = PastryType::salty;
	if (type == "bread")
		t = PastryType::bread;
	return Filter.FilterByType(t);
}

vector<Pastry> Controller::SortByName()
{
	vector<Pastry> Sorted;
	Sorted = Bakery.get_all();
	SortingCriteria Sorting(Sorted);
	return Sorting.SortByName();;
}

vector<Pastry> Controller::SortByStock()
{
	vector<Pastry> Sorted;
	Sorted = Bakery.get_all();
	SortingCriteria Sorting(Sorted);
	return Sorting.SortByStock();;
}

vector<Pastry> Controller::SortByPrice()
{
	vector<Pastry> Sorted;
	Sorted = Bakery.get_all();
	SortingCriteria Sorting(Sorted);
	return Sorting.SortByPrice();
}

vector<Pastry> Controller::SortBySugar()
{
	vector<Pastry> Sorted;
	Sorted = Bakery.get_all();
	SortingCriteria Sorting(Sorted);
	return Sorting.SortBySugar();
}

vector<Pastry> Controller::SortByType()
{
	vector<Pastry> Sorted;
	Sorted = Bakery.get_all();
	SortingCriteria Sorting(Sorted);
	return Sorting.SortByType();
}

vector<Pastry> Controller::GetContent()
{
	return Bakery.get_all();
}