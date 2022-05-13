#pragma once
#include <string>
#include <exception>
using std::string;

/**
 * Class that manages exceptions on the Repo and FileRepo.
 */
class RepoException : public std::exception {
private:
    string message; /*!< message given when throwing the current exception */ 
public:
    RepoException(const string&);
    const string& get_message() const;
};