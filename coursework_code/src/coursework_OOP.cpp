#include "classes/Menu.h"
#include "CommonHeaders.h"

using namespace std;

int main()
{
    Menu menu;
    srand(static_cast<unsigned int>(time(nullptr)));
    while (menu.createCompanyMenu())
        ;
    while (menu.CompanyMenu())
        ;
    ClearScreen();
    cout << "Завершения выполнения программы \n";

    Pause();
    return 0;
}