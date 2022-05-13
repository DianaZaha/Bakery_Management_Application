#include "RepoExceptions.h"

/** Creates an exaception with a message
 * .
 * 
 * \param _message the message that states what the problem is
 */
RepoException::RepoException(const string& _message)
    :std::exception(), message{ _message }
{
}

/** Gives the message of the current exception
 * .
 * Used so we can distinguse 2 RepoExceptions from each other in Tests and UI
 * \return the message of the current exception
 */

const string& RepoException::get_message() const
{
    return this->message;
}
