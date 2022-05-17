#pragma once

#include "Pastry.h"
#include "Action.h"

#include "Repo.h"
#include "FileRepo.h"

#include "FilteringCriteria.h"
#include "SortingCriteria.h"

#include "UI.h"

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
    void TestController();

public:
    void TestAll();
};

