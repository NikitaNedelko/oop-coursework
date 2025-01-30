#include <iostream>
#include "classes/Menu.h"

using namespace std;

int main()
{
    Menu menu;
    srand(static_cast<unsigned int>(time(nullptr)));
    while (menu.createCompanyMenu())
        ;
    while (menu.CompanyMenu())
        ;
    system("cls");
    cout << "Завершения выполнения программы \n";

    system("pause");
    return 0;
}