
#pragma once
#include "Repo.h"
#include "Pastry.h"
#include <string>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;


/**
 * Class that manages a Repo which stores its data in a csv.
 */
template <typename TElem>
class FileRepo : public Repo<TElem> {

private:

    string filepath; /** the name of the file where the Repository stores its data */

    /**
     * Reads all elements from the given file.
     * 
     * \throw error if the file couldn't be opened
     */
    void read_all_from_file() {
        ifstream ifs{ this->filepath };
        this->elems.clear();
        if (!ifs.is_open())
            throw RepoException("Couldn't open the file\n");
        TElem r;
        while (ifs >> r) {
            this->elems.push_back(r);
        }
    };

    /**
     * Writes all elements from the given file.
     */
    void write_all_to_file() {
        ofstream ofs{ this->filepath };
        std::for_each(this->elems.begin(), this->elems.end(), [&](const auto& x) {
            ofs << x <<"\n";
            });
    };

public:

    /** A constructor.
     *
     * The default constructor.
     */
    FileRepo()
    {
    };

    /**
     * A constructor.
     * Creates a Repository that manages a file given at filepaht and loads its element
     * \param _filepath the name of the file the Repository will manage
     */
    FileRepo(const string& _filepath) :Repo<TElem>(), filepath{ _filepath } 
    {
        this->read_all_from_file();
    };

    /**
     * Copy Constructor(Rule of 3).
     * Creates a new Repository that manages a the same file as the one of the Repository given and loads its element
     * \param other the File Repositoy that should be copied
     */
    FileRepo(const FileRepo<TElem>& other) : Repo<TElem>(), filepath{ other.filepath } 
    {
        this->read_all_from_file();
    };

    /** Copy assignment operator (Rule of 3).
     * Here we overriden the asigment operator
     * \param other the File Repository that should be copied
     * \return The newly formed File Repository
     */
    FileRepo<TElem>& operator=(const FileRepo<TElem>& other)
    {
        Repo<TElem>();
        filepath = other.filepath;
        return *this;
    };

    void add(const TElem& elem){
        this->read_all_from_file();
        Repo<TElem>::add(elem);
        Repo<TElem>::sort();
        this->write_all_to_file();
        this->elems.clear();
    };

    void update(const TElem& elem){
        this->read_all_from_file();
        Repo<TElem>::update(elem);
        this->write_all_to_file();
        this->elems.clear();
    };

    void remove(const TElem& elem){
        this->read_all_from_file();
        Repo<TElem>::remove(elem);
        this->write_all_to_file();
        this->elems.clear();
    };

    const TElem& search(const TElem& elem){
        this->read_all_from_file();
        return Repo<TElem>::search(elem);
    };

    const vector<TElem>& get_all() 
    {
        this->read_all_from_file();
        return Repo<TElem>::get_all();
    };

    int size(){
        this->read_all_from_file();
        return Repo<TElem>::size();
    };

    ~FileRepo()
    {
    };
};
