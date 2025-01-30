// #include "Accountant.h"
// #include "SalaryDatabase.h"
// #include "Director.h"
// #include "enums/position.h"
// #include <iostream>
// #include <iomanip>

// using namespace std;

// Accountant::Accountant(const PersonalData &personalData, SalaryDatabase &salaryDatabase)
//     : salaryDatabase(salaryDatabase)
// {
//     this->personalData = personalData;
//     setSalary(salaryDatabase.getMinimalSalary(Position::Accountant));
// }

// void Accountant::setFirstName(const std::string &firstName)
// {
//     personalData.firstName = firstName;
// }

// std::string Accountant::getFirstName() const
// {
//     return personalData.firstName;
// }

// void Accountant::setLastName(const std::string &lastName)
// {
//     personalData.lastName = lastName;
// }

// std::string Accountant::getLastName() const
// {
//     return personalData.lastName;
// }

// void Accountant::setMiddleName(const std::string &middleName)
// {
//     personalData.middleName = middleName;
// }

// std::string Accountant::getMiddleName() const
// {
//     return personalData.middleName;
// }

// void Accountant::setSalary(double salary)
// {
//     personalData.salary = salary;
// }

// double Accountant::getSalary() const
// {
//     return personalData.salary;
// }

// void Accountant::applyBonuses(Person *employee, double bonus, Director &director)
// {
//     if (bonus < 100 && bonus > 0)
//         throw invalid_argument("Премия не может быть меньше 100 рублей");
//     if (bonus > employee->getSalary())
//         throw invalid_argument("Премия не может быть больше оклада");

//     double currentBudgetBonuses =
//         director.getApprovedBudget()[Department::Bonuses] + getEmployeeBonus(employee);

//     if (bonus > currentBudgetBonuses)
//         throw invalid_argument("Недостаточно бюджета для выдачи премий!");

//     director.approveBudget(Department::Bonuses,
//                            currentBudgetBonuses - bonus); // изменение бюджета бонусов
//     employeesBonuses[employee] = bonus;
//     cout << "Изменена премия для " << employee->getMiddleName() << ' ' << employee->getFirstName()
//          << " " << employee->getLastName() << " на " << fixed << setprecision(2)
//          << employeesBonuses[employee] << " руб." << endl;
// }

// void Accountant::updateEmployeesRate(Director &director)
// {
//     for (const auto &[employee, position] : director.getEmployees())
//     {
//         // Проверяем, есть ли уже ставка для сотрудника
//         if (employeesRate.find(employee) != employeesRate.end())
//             continue;
//         setRate(employee, employee->getSalary() / salaryDatabase.getMinimalSalary(position),
//                 director);
//     }
// }

// void Accountant::setRate(Person *employee, double newRate, Director &director)
// {
//     // Проверка минимальной ставки
//     if (newRate < 0.1)
//         throw invalid_argument("Ставка не может быть ниже 0.1.");

//     Position position = getEmployeeType(employee);

//     // Получение базовой зарплаты и текущего бюджета отдела
//     double baseSalary = salaryDatabase.getMinimalSalary(position);
//     double currentBudget = director.getApprovedBudget()[Department(int(position))];

//     // Проверка, что сотрудник существует в базе ставок
//     auto it = employeesRate.find(employee);
//     if (it != employeesRate.end()) // если сотрудник найден (старый)
//     {
//         double oldRate = it->second; // Текущая ставка сотрудника
//         double oldSalary = baseSalary * oldRate;
//         // Рассчитываем изменение бюджета
//         double newSalary = baseSalary * newRate;
//         double salaryDifference = newSalary - oldSalary;
//         if (salaryDifference > 0 && currentBudget < salaryDifference)
//             throw invalid_argument("Недостаточно бюджета для увеличения ставки. " +
//                                    to_string(salaryDifference - currentBudget) + " руб.\n");
//         // Обновление ставки и бюджета отдела
//         employeesRate[employee] = newRate;
//         director.getApprovedBudget()[Department(int(position))] -= salaryDifference;
//         employee->setSalary(newSalary);

//         cout << "Ставка сотрудника " << employee->getMiddleName() << " изменена на " << newRate
//              << ". Зарплата теперь " << employee->getSalary() << ".\n";
//         return;
//     }

//     // Обновление ставки и бюджета отдела
//     employeesRate[employee] = newRate;

//     return;
// }

// double Accountant::getEmployeeRate(Person *employee) const { return employeesRate.at(employee); }

// double Accountant::getEmployeeBonus(Person *employee) const
// {
//     auto it = employeesBonuses.find(employee);
//     if (it != employeesBonuses.end())
//     {
//         return it->second;
//     }
//     return 0; // Возвращаем 0, если ключ не найден
// }

// map<Person *, double> Accountant::getEmployeesRates() const { return employeesRate; }

// SalaryDatabase &Accountant::getSalaryDataBase() { return salaryDatabase; }

// void Accountant::displayInfo()
// { // Заголовок таблицы
//     cout << left << setw(3) << "№ |" << setw(10) << "Должность|" << setw(45)
//          << "    Фамилия    |      Имя      |   Отчество    |"
//          << "   Зарплата   |" << setw(6) << "Ставка|" << "    Премия    |" << endl;
//     cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
//          << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+'
//          << string(6, '-') << '+' << string(14, '-') << '+' << endl;

//     // Данные о бухгалтере
//     cout << left << setw(2) << 0 << setw(10) << "|" + toStringEnum(Position::Accountant) << setw(16)
//          << "|" + getMiddleName() << setw(16) << "|" + getFirstName() << setw(16)
//          << "|" + getLastName() << "|" << setw(9) << fixed << setprecision(2) << getSalary()
//          << " руб.|" << setw(6) << fixed << setprecision(2) << getEmployeeRate(this) << "|"
//          << setw(9) << fixed << setprecision(2) << getEmployeeBonus(this) << " руб.|" << endl;

//     cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
//          << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+'
//          << string(6, '-') << '+' << string(14, '-') << '+' << endl;
// }

// Position Accountant::getEmployeeType(
//     Person *employee) // определяем что за работник относительно Person *
// {
//     if (dynamic_cast<Driver *>(employee))
//         return Position::Driver;
//     else if (dynamic_cast<SecurityGuard *>(employee))
//         return Position::SecurityGuard;
//     else if (dynamic_cast<Director *>(employee))
//         return Position::Director;
//     else if (dynamic_cast<Accountant *>(employee))
//         return Position::Accountant;
//     else if (dynamic_cast<Secretary *>(employee))
//         return Position::Secretary;

//     throw invalid_argument("Неизвестный тип работника");
// }
