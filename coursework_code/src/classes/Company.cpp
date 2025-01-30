#include "classes/Company.h"

using namespace std;

Director &Company::getDirector() { return director; }

void Company::displayInfo() const
{
    cout << "Название компании: " << name << endl;
    cout << "Директор: " << director.getFirstName() << " " << director.getLastName() << endl;
    cout << "Зарплата: " << director.getSalary() << " руб." << endl;
}
void Company::setName(string name) { this->name = name; }
string Company::getName() const { return name; }
