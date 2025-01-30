#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <vector>
#include <string>
#include "enums/position.h"
#include "Company.h"
#include "Driver.h"
#include "SecurityGuard.h"
#include "Director.h"
#include "Accountant.h"
#include "Secretary.h"

using namespace std;
using namespace app;

// Класс для работы с меню
class Menu
{
private:
    int choice;
    // список всех компаний
    vector<Company> companies;

public:
    // ------------------------manualInput------------------------
    // получение типа сотрудника по объекту Person *
    Position getEmployeeType(Person *employee);

    // вывод всех сотрудников в таблицу (должность, ФИО, ЗП)
    void displayAllEmployees(Director &director, vector<Person *> &employees);
    // вывод определенного сотрудника в таблицу (должность, ФИО, ЗП)
    void displayAllEmployeesWithInt(Director &director, vector<int> &indexs);
    // вывод всех сотрудников в таблицу (должность, ФИО, ЗП, ставка, премия)
    void displayAllEmployeesWithRatesAndBonuses(Director &director, Accountant &accountant);
    // вывод всех сотрудников в таблицу (должность, ФИО, ЗП, ставка)
    void displayAllEmployeesWithRates(Director &director, Accountant &accountant, vector<Person *> &employees);
    // вывод всех сотрудников в таблицу (должность, ФИО, ЗП, премия)
    void displayAllEmployeesWithBonuses(Director &director, Accountant &accountant, vector<Person *> &employees);
    // вывод всех должностей их коэффициент и зарплату
    void displayALLPositionsWithKoef(Accountant &accountant);
    // получение массива компаний
    vector<Company> getListOfCompanies() const;
    // создание компании в ручную
    bool createCompanyManually(Company &company);
    // изменение названия компании
    bool changeNameCompany(Company &Company);
    // удаление компании
    bool deleteCompany(Company &companyToRemove);
    // изменение ФМО сотрудника
    bool setFIO(Person &person);
    // меню нанять на работу от лица директора, с выбором должности нового рабочего, ввода ФИО  (проверка что бухгалтер и секретарь уже есть в компании и что бюджета отдела хватит на найм рабочего)
    bool hireEmployeeMenu(Director &director);
    // меню выбора сотрудника на увольнение (ЗП сотрудника возвращается в бюджет отдела)
    bool terminateEmployeeMenu(Director &director);
    // создание встреч. Задается время, название, участники и место встречи
    bool createMeeting(Secretary &secretary, Director &director);
    // вывод всех созданных встреч
    bool getParticipantOfMeeting(Secretary &secretary);
    // выбор встречи для удаление
    bool deleteMeeting(Secretary &secretary);
    // ------------------------RANDOM------------------------
    // Функция для генерации случайного имени
    string generateRandomFirstName() const;
    // Функция для генерации случайной фамилии
    string generateRandomMiddleName() const;
    // Функция для генерации случайного отчества
    string generateRandomLastName() const;
    // Функция для генерации случайного названия компании
    string generateRandomCompanyName() const;
    // Функция для генерации случайного специального оборудования
    Equipment generateRandomSpecialEquipment();
    // Функция для генерации случайного города
    string generateRandomCity();
    // Функция для генерации случайной даты в диапазоне от сегодня до года вперед
    Date generateRandomDate();
    // Функция для генерации случайной комнаты
    string generateRandomRoom();
    // Функция для генерации случайного типа прав для водителя
    DriverLicense generateRandomDriverLicense();
    // Функция для генерации случайного транспорта в зависимости от типа прав
    VehicleType generateRandomVehicle(const DriverLicense &license);

    // Функция для создания компании с рандомными значениями
    Company createCompanyRandom();

    // ------------------------UI------------------------
    // ввод положительной цифры
    bool inputSingleInt(int &digit, const int start, const int end);
    // ввод строки
    bool inputString(string &str, const int &minLen = 2, const int &maxLen = 15, bool firstBigLetter = 1, bool allowNumbers = 0);
    // ввод числа int
    bool inputInt(int &number, const int &min = INT_MIN / 10, const int &max = INT_MAX / 10,
                  const string &key = "NULL", const bool minus = 0,
                  const bool point = 0);
    // ввод double
    bool inputDouble(double &number, const double &min = __DBL_MIN__ / 10,
                     const double &max = __DBL_MAX__ / 10, const string &key = "NULL",
                     const bool minus = 0, const bool point = 1,
                     int decimalLimit = 2);
    // очистка консоли и вывод сообщения "нажмите esc чтобы выйти"
    void clearConsole();

    // ------------------------MENU------------------------
    // меню создания компании
    bool createCompanyMenu();
    // меню выбора создать или управлять компаниями
    bool CompanyMenu();
    // меню выбора компании для управления
    bool manageCompaniesMenu();
    // меню управления одной компанией
    bool workWithCompany(Company &company);
    // управление сотрудниками компании
    bool manageEmployeesMenu(Director &director);
    // управление бюджетом отделов
    bool manageBudgetDepartmentsMenu(Director &director);
    // изменение ставок сотрудников
    bool setEmployeesRatesMenu(Accountant &accountant, Director &director);
    // изменение ставок сотрудников
    bool setEmployeesBonusesMenu(Accountant &accountant, Director &director);
    // изменение коэффициента должности
    bool setCoefficientMenu(Accountant &accountant, Director &director);
    // меню управления встречами
    bool meetingManageMenu(Secretary &secretary, Director &director);
    // меню изменения статуса отделов
    bool manageStatusLocationsMenu(SecurityGuard &securityGuard);
    // меню изменения спец средств
    bool manageSpecialEquipmentMenu(SecurityGuard &securityGuard);
    // меню выбора места, куда поедет водитель
    bool manageDriverDestinationMenu(Driver &driver);
    // меню добавления/удаление водительских прав
    bool manageDriverLicenseCategoriesMenu(Driver &driver);
    // меню добавления/удаление транспорта
    bool manageDriverVehiclesMenu(Driver &driver);

    // функции директора
    bool manageEmployeeMenu(Director &director);
    // функции бухгалтера
    bool manageEmployeeMenu(Accountant *accountant, Director &director);
    // функции секретаря
    bool manageEmployeeMenu(Secretary *secretary, Director &director);
    // функции охранника
    bool manageEmployeeMenu(SecurityGuard *securityGuard);
    // функции водителя
    bool manageEmployeeMenu(Driver *driver);
};

#endif // MENU_H