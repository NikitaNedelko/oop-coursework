#ifndef DIRECTOR_H
#define DIRECTOR_H

#include <map>
#include <string>
#include "Person.h"
#include "enums/department.h"
#include "enums/position.h"
#include "structs/personal_data.h"

#include "SalaryDatabase.h"

// класс Директор, наследуемый от Person
class Director : public Person
{
private:
    PersonalData personalData;

    SalaryDatabase salaryDatabase;                  // Ссылка на базу зарплат
    std::map<Person *, Position> employees;         // Человек -> Должность
    std::map<Department, double> departmentBudgets; // Название отдела -> бюджет

public:
    Director();

    Director(const PersonalData &personalData, SalaryDatabase &salaryDatabase);

    // Геттеры и сеттеры для полей Director
    void setFirstName(const std::string &firstName) override;
    std::string getFirstName() const override;
    void setLastName(const std::string &lastName) override;
    std::string getLastName() const override;
    void setMiddleName(const std::string &middleName) override;
    std::string getMiddleName() const override;
    void setSalary(const double salary) override;
    double getSalary() const override;

    // список сотрудников в подчинении -
    std::map<Person *, Position> getEmployees() const;
    // задать бюджет на отдел -
    void approveBudget(const Department &department, double budget);
    // получить бюджет отдела -
    std::map<Department, double> &getApprovedBudget();
    // нанять работника -
    void hireEmployee(Person *employee, const Position &position);
    // уволить работника -
    void terminateEmployee(Person *employee);
    // получение базы данных зарплат -
    SalaryDatabase &getSalaryDataBase();
    // вся информация о классе -
    void displayInfo();
    // находим бухгалтера среди работников -
    Person *findAccountant() const;
    // находим секретаря среди работников -
    Person *findSecretary() const;
};

#endif // DIRECTOR_H