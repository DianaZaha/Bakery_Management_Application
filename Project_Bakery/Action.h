#pragma once
#include "Pastry.h"

/**
 * This Class Tells us what kind of Action we just performed on the Repo or FileRepo
 */
enum class ActionType {
	addition = 0, deletion = 1, update = 2
};

/**
 * Class that manages an action that have been performed and what elements it has affected.
 */
template<typename TElem>
class Action {
private:
	ActionType Act; /** Last action performed on the Repo according to ActionType */ 
	TElem Elem; /** the element that have been added/ removed from the Repo or FileRepo */ 
	TElem Elem1; /** the element that have been updated in the Repo or FileRepo*/ 
public:
	/**
	 * The default constructor.
	 * 
	 */
	Action()
	{
		Act = ActionType:: addition;
	}
	/** A constructor
	 * .
	 * 
	 * \param _Act
	 * \param _Elem the element that have been added/ removed from the Repo or FileRepo
	 * \param _Elem1 the element that have been updated in the Repo or FileRepo
	 */
	Action(ActionType _Act, TElem _Elem, TElem _Elem1):
		Act{ _Act }, Elem{ _Elem }, Elem1{ _Elem1 }
	{
	}

	/** Returns the current action acording to ActionType
	* .
	*
	* \return the current action acording to ActionType
	*/
	ActionType getAction()
	{
		return Act;
	}

	/** Returns element
	* .
	* Returns the element that have been added/removed from the Repo or File Repo
	* \return element
	*/
	TElem getElem()
	{
		return Elem;
	}

	/** Returns element
	* .
	* Returns the element that have been added/removed from the Repo or File Repo
	* \return element
	*/
	TElem getElem1()
	{
		return Elem1;
	}

};

