#ifndef PERSON_H
#define PERSON_H

#include "CommonHeaders.h"

// базовый класс Человек
class Person
{
public:
    // свойства
    virtual void setFirstName(const std::string &firstName) = 0;   // Изменить имя
    virtual std::string getFirstName() const = 0;                  // Получить имя
    virtual void setLastName(const std::string &lastName) = 0;     // Изменить отчество
    virtual std::string getLastName() const = 0;                   // Получить отчество
    virtual void setMiddleName(const std::string &middleName) = 0; // Изменить фамилию
    virtual std::string getMiddleName() const = 0;                 // Получить фамилию
    virtual void setSalary(const double salary) = 0;               // Изменить ЗП
    virtual double getSalary() const = 0;                          // Получить ЗП

    virtual ~Person() = default;
};

#endif // PERSON_H