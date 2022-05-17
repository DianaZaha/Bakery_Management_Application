#include <iostream>
#include "Tests.h"
#include "FileRepo.h"
#include "UI.h"

int main() {
    Tests t;
    t.TestAll();

    UI U;
    U.displayMenu();
    return 0;
}
