#include "classes/SecurityGuard.h"
#include "utils/enum_to_string.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace app;

SecurityGuard::SecurityGuard(const PersonalData &personalData, const Equipment &equipment)
    : specialEquipment(equipment)
{
    setFirstName(personalData.firstName);
    setMiddleName(personalData.middleName);
    setLastName(personalData.lastName);
    specialEquipment = Equipment::Flashlight;
    for (string dep : departments)
    {
        locations[dep] = "Нужна проверка";
    }
}

void SecurityGuard::setFirstName(const std::string &firstName)
{
    personalData.firstName = firstName;
}

std::string SecurityGuard::getFirstName() const
{
    return personalData.firstName;
}

void SecurityGuard::setLastName(const std::string &lastName)
{
    personalData.lastName = lastName;
}

std::string SecurityGuard::getLastName() const
{
    return personalData.lastName;
}

void SecurityGuard::setMiddleName(const std::string &middleName)
{
    personalData.middleName = middleName;
}

std::string SecurityGuard::getMiddleName() const
{
    return personalData.middleName;
}

void SecurityGuard::setSalary(double salary)
{
    personalData.salary = salary;
}

double SecurityGuard::getSalary() const
{
    return personalData.salary;
}

vector<string> SecurityGuard::allDepartments() { return departments; }
vector<string> SecurityGuard::allStatuses() { return statuses; }
void SecurityGuard::setSecurityStatus(std::string &department, std::string &status)
{
    locations[department] = status;
}
void SecurityGuard::generateIncidentReport() const
{
    cout << "\nОтчет о безопасности:\n";
    cout << "Отдел\t\tСтатус\n";
    cout << "--------------------------------------------------------\n";
    int i = 0;
    for (const auto &location : departments)
    {
        cout << ++i << ") " << location << "\t" << locations.at(location) << endl;
    }
}
void SecurityGuard::setSpecialEquipment(const Equipment equipment) { specialEquipment = equipment; }
Equipment SecurityGuard::getSpecialEquipment() const { return specialEquipment; }
void SecurityGuard::displayInfo() const
{
    cout << left << setw(3) << "№ |" << setw(10) << "Должность|" << setw(45)
         << "    Фамилия    |      Имя      |   Отчество    |"
         << "   Зарплата   |" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
         << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

    cout << left << setw(2) << 0 << setw(10) << "|" + toStringEnum(Position::SecurityGuard)
         << setw(16) << "|" + getMiddleName() << setw(16) << "|" + getFirstName() << setw(16)
         << "|" + getLastName() << "|" << setw(9) << fixed << setprecision(2) << getSalary()
         << " руб.|" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
         << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

    cout << "Спец средство: " << toStringEnum(getSpecialEquipment());
}
