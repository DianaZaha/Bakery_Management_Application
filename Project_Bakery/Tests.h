#pragma once

#include "Pastry.h"
#include "Repo.h"

/**
 * Class that manages testing the components of the project.
 * @note These tests exclude the UI
 */

class Tests
{
private:
    void TestDomain();
    void TestFilteringandSorting();
    void TestRepo();

public:
    void TestAll();
};

