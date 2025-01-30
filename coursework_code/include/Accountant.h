// #ifndef ACCOUNTANT_H
// #define ACCOUNTANT_H

// #include <map>
// #include <string>
// #include "SalaryDatabase.h"
// #include "structs/personal_data.h"
// #include "Person.h"
// #include "Director.h"

// // Предварительное объявление класса Director
// class Director;

// class Accountant : public Person
// {
// private:
//     PersonalData personalData;
//     SalaryDatabase salaryDatabase;               // Ссылка на базу зарплат
//     std::map<Person *, double> employeesRate;    // Хранение ставки по каждому сотруднику
//     std::map<Person *, double> employeesBonuses; // Хранение премиальных по каждому сотруднику

// public:
//     Accountant(const PersonalData &personalData, SalaryDatabase &salaryDatabase);

//     // Геттеры и сеттеры для полей Accountant
//     void setFirstName(const std::string &firstName) override;
//     std::string getFirstName() const override;
//     void setLastName(const std::string &lastName) override;
//     std::string getLastName() const override;
//     void setMiddleName(const std::string &middleName) override;
//     std::string getMiddleName() const override;
//     void setSalary(double salary) override;
//     double getSalary() const override;

//     // изменение премии сотрудников
//     void applyBonuses(Person *employee, const double bonus, Director &director);
//     // изменение ставки сотрудников
//     void setRate(Person *employee, double rate, Director &director);
//     // добавление ставок сотрудников в массив ставок
//     void updateEmployeesRate(Director &director);
//     // получение ставки сотрудника
//     double getEmployeeRate(Person *employee) const;
//     // получение премии сотрудника
//     double getEmployeeBonus(Person *employee) const;
//     // выводим базу данных зарплат
//     SalaryDatabase &getSalaryDataBase();
//     // определяем что за работник относительно Person *
//     Position getEmployeeType(Person *employee);
//     // все ставки по каждому сотруднику
//     std::map<Person *, double> getEmployeesRates() const;
//     // вся информация о классе
//     void displayInfo();
// };

// #endif // ACCOUNTANT_H