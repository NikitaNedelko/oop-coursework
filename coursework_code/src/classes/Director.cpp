#include "classes/Director.h"
#include "utils/enum_to_string.h"
#include "classes/SalaryDatabase.h"

using namespace app;

Director::Director()
{
    setFirstName("NULL");
    setMiddleName("NULL");
    setLastName("NULL");
    setSalary(salaryDatabase.getMinimalSalary(Position::Director));
    approveBudget(Department::Bonuses, 20000);
    approveBudget(Department::Finance, 200000);
    approveBudget(Department::Management, 200000);
    approveBudget(Department::Security, 200000);
    approveBudget(Department::Transportation, 200000);
    approveBudget(Department::Executive, 100000 - getSalary());
}

Director::Director(const PersonalData &personalData, SalaryDatabase &salaryDatabase)
    : salaryDatabase(salaryDatabase)
{
    setFirstName(personalData.firstName);
    setMiddleName(personalData.middleName);
    setLastName(personalData.lastName);
    setSalary(salaryDatabase.getMinimalSalary(Position::Director));
    approveBudget(Department::Bonuses, 20000);
    approveBudget(Department::Finance, 200000);
    approveBudget(Department::Management, 200000);
    approveBudget(Department::Security, 200000);
    approveBudget(Department::Transportation, 200000);
    approveBudget(Department::Executive, 100000 - getSalary());
}

// Геттеры и сеттеры для полей Director
void Director::setFirstName(const std::string &firstName) { personalData.firstName = firstName; }
std::string Director::getFirstName() const { return personalData.firstName; }
void Director::setLastName(const std::string &lastName) { personalData.lastName = lastName; }
std::string Director::getLastName() const { return personalData.lastName; }
void Director::setMiddleName(const std::string &middleName) { personalData.middleName = middleName; }
std::string Director::getMiddleName() const { return personalData.middleName; }
void Director::setSalary(const double salary) { personalData.salary = salary; }
double Director::getSalary() const { return personalData.salary; }

std::map<Person *, Position> Director::getEmployees() const { return employees; }

void Director::approveBudget(const Department &department, double budget)
{
    departmentBudgets[department] = budget;
}

std::map<Department, double> &Director::getApprovedBudget() { return departmentBudgets; }

void Director::hireEmployee(Person *employee, const Position &position)
{
    double baseSalary = salaryDatabase.getMinimalSalary(position);
    double currentBudget = departmentBudgets[Department(int(position))];

    // Проверяем бюджет: нужен бюджет хотя бы на минимальную ставку 0.1
    if (currentBudget < baseSalary * 0.1)
        throw std::invalid_argument("Недостаточно бюджета для найма на минимальную ставку");

    // установка ставки
    double maxRate = currentBudget / baseSalary;
    if (maxRate > 1.0)
        maxRate = 1.0;
    if (maxRate < 0.1)
        throw std::invalid_argument("Бюджета недостаточно даже для минимальной ставки.");

    employee->setSalary(baseSalary * maxRate);

    // установка начальной ставки и обновление бюджета
    employees[employee] = position;
    departmentBudgets[Department(int(position))] -= baseSalary * maxRate;

    std::cout << toStringEnum(position) << ' ' << employee->getMiddleName() << " нанят на работу. "
              << "C зарплатой " << employee->getSalary() << std::endl;
}

void Director::terminateEmployee(Person *employee)
{
    // Проверяем, что сотрудник существует в списке
    auto it = employees.find(employee);
    if (it == employees.end())
        throw std::invalid_argument("Сотрудник не найден.");

    // Получаем позицию и зарплату сотрудника
    Position position = it->second;
    double salary = employee->getSalary();

    // Возвращаем зарплату в бюджет отдела
    departmentBudgets[Department(int(position))] += salary;

    std::cout << "Сотрудник " << employee->getMiddleName() << " уволен. Бюджет отдела "
              << toStringEnum(Department(int(position))) << " восстановлен на " << salary << "\n";

    // Удаляем сотрудника из списка
    employees.erase(it);
    delete employee;
}

SalaryDatabase &Director::getSalaryDataBase() { return salaryDatabase; }

void Director::displayInfo()
{
    std::cout << std::left << std::setw(3) << "№ |" << std::setw(10) << "Должность|" << std::setw(45)
              << "    Фамилия    |      Имя      |   Отчество    |"
              << "  Зарплата   |" << std::endl;
    std::cout << std::string(2, '-') << '+' << std::string(9, '-') << '+' << std::string(15, '-') << '+'
              << std::string(15, '-') << '+' << std::string(15, '-') << '+' << std::string(13, '-') << '+' << std::endl;

    std::cout << std::left << std::setw(2) << 0 << std::setw(10) << "|" + toStringEnum(Position::Director) << std::setw(16)
              << "|" + getMiddleName() << std::setw(16) << "|" + getFirstName() << std::setw(16)
              << "|" + getLastName() << "|" << std::fixed << std::setprecision(2) << getSalary() << " руб.|"
              << std::endl;
    std::cout << std::string(2, '-') << '+' << std::string(9, '-') << '+' << std::string(15, '-') << '+'
              << std::string(15, '-') << '+' << std::string(15, '-') << '+' << std::string(13, '-') << '+' << std::endl;

    std::cout << "\nБюджет отделов:\n";
    for (auto &department : getApprovedBudget())
    {
        std::cout << std::setw(20) << toStringEnum(department.first) // Название отдела
                  << std::setw(7) << department.second               // Бюджет
                  << " руб." << std::endl;
    }
}

Person *Director::findAccountant() const
{
    for (const auto &employee : employees)
        if (employee.second == Position::Accountant)
            return employee.first; // Возвращаем указатель на бухгалтера
    return nullptr;                // Бухгалтер не найден
}

Person *Director::findSecretary() const
{
    for (const auto &employee : employees)
        if (employee.second == Position::Secretary)
            return employee.first; // Возвращаем указатель на секретаря
    return nullptr;                // секретарь не найден
}
