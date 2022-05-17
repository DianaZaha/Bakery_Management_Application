#pragma once
#include <vector>
#include <algorithm>
#include <ostream>
#include "RepoExceptions.h"

using std::ostream;
using std::vector;

/** 
 *Class that manages a repository of an element.
 */
template <typename TElem>
class Repo {
protected:
    vector<TElem> elems; /** a vector formed with the current elements */ 
public:
    /** A constructor.
    *
    * The default constructor.
    */
    Repo() {
    };

    /**
     * adds an eleemnt to the current repository.
     * 
     * \param elem the element to be added
     * \throw error if the element already exists
     */
    virtual void add(const TElem& elem) {
        auto it = std::find(this->elems.begin(), this->elems.end(), elem);
        if (it != this->elems.end()) {
            throw RepoException("existent element!\n");
        }
        this->elems.push_back(elem);
    };

    /**
     * updates an eleemnt to the current repository.
     *
     * \param elem the element to be update already containing its new values
     * \throw error if the element dooesn't already exist
     */

    virtual void update(const TElem& elem) {
        auto it = std::find(this->elems.begin(), this->elems.end(), elem);
        if (it == this->elems.end()) {
            throw RepoException("inexistent element!\n");
        }
        this->elems[it - this->elems.begin()] = elem;
    };

    /**
    * deletes an eleemnt to the current repository.
    *
    * \param elem the element to be deleted
    * \throw error if the element dooesn't already exist
    */
    virtual void remove(const TElem& elem) {
        auto it = std::find(this->elems.begin(), this->elems.end(), elem);
        if (it == this->elems.end()) {
            throw RepoException("inexistent element!\n");
        }
        this->elems.erase(it);
    };

    /** Sorts the current repository
     * .
     */

    virtual void sort() {
        std::sort(this->elems.begin(), this->elems.end());
    };

    /**
     * Searches a given element in the current repository.
     * 
     * \param elem the element searched
     * \return the element if we found it or the NULL pointer if it not in the repository
     */
    virtual const TElem& search(const TElem& elem) {
        auto it = std::find(this->elems.begin(), this->elems.end(), elem);
        if (it == this->elems.end()) {
            throw RepoException("inexistent element!\n");
        }
        return *it;
    };

    /** Return a vector containing all the elements
     * .
     * 
     * \return a vector containing all the elements in the repository
     */
    virtual const vector<TElem>& get_all() {
        return this->elems;
    };

    /** Gives the number of elements in the current repository
     * .
     * 
     * \return number of elements in the current repository
     */
    virtual int size() {
        return this->elems.size();
    };

    /**
     * A default constructor.
     *  
    */
    ~Repo() {
    };
};
