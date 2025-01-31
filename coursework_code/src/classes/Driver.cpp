#include "classes/Driver.h"
#include "utils/enum_to_string.h"

using namespace std;
using namespace app;

Driver::Driver(const PersonalData &personalData, DriverLicense licenseCategories,
               VehicleType vehicles)
{
    setFirstName(personalData.firstName);
    setMiddleName(personalData.middleName);
    setLastName(personalData.lastName);
    addLicenseCategory(licenseCategories);
    addVehicle(vehicles);
    destination = "Не задано";
    cities = {"Москва", "Санкт-Петербург",
              "Нижний Новгород", "Казань",
              "Челябинск", "Омск",
              "Ростов-на-Дону", "Уфа",
              "Не задано"};
}

void Driver::setFirstName(const std::string &firstName)
{
    personalData.firstName = firstName;
}

std::string Driver::getFirstName() const
{
    return personalData.firstName;
}

void Driver::setLastName(const std::string &lastName)
{
    personalData.lastName = lastName;
}

std::string Driver::getLastName() const
{
    return personalData.lastName;
}

void Driver::setMiddleName(const std::string &middleName)
{
    personalData.middleName = middleName;
}

std::string Driver::getMiddleName() const
{
    return personalData.middleName;
}

void Driver::setSalary(double salary)
{
    personalData.salary = salary;
}

double Driver::getSalary() const
{
    return personalData.salary;
}

void Driver::addLicenseCategory(const DriverLicense &category)
{
    licenseCategories.push_back(category);
}

void Driver::addVehicle(const VehicleType &vehicle)
{
    vehicles.push_back(vehicle);
}

void Driver::changeDestination(const std::string &newDestination)
{
    destination = newDestination;
}

std::vector<DriverLicense> &Driver::getLicenseCategories()
{
    return licenseCategories;
}

std::vector<VehicleType> &Driver::getVehicles()
{
    return vehicles;
}

const std::vector<std::string> Driver::getCities()
{
    return cities;
}

void Driver::displayInfo() const
{
    cout << left << setw(3) << "№ |" << setw(10) << "Должность|" << setw(45)
         << "    Фамилия    |      Имя      |   Отчество    |"
         << "   Зарплата   |" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
         << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

    cout << left << setw(2) << 0 << setw(10) << "|" + toStringEnum(Position::Driver) << setw(16)
         << "|" + getMiddleName() << setw(16) << "|" + getFirstName() << setw(16)
         << "|" + getLastName() << "|" << setw(9) << fixed << setprecision(2) << getSalary()
         << " руб.|" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
         << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

    if (!licenseCategories.empty())
    {
        cout << "Имеющиеся категории прав : ";
        for (DriverLicense dl : licenseCategories)
        {
            cout << toStringEnum(dl) << " ";
        }
        cout << endl;
    }
    cout << endl;

    if (!vehicles.empty())
    {
        cout << "Имеющиеся транспортные средства : ";
        for (VehicleType vt : vehicles)
        {
            cout << toStringEnum(vt) << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Выехал в город - " << destination;
    cout << endl;
}
