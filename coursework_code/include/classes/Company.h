#ifndef COMPANY_H
#define COMPANY_H

#include <string>
#include "Director.h"

class Company // класс для управления компанией
{
private:
    std::string name;  // название компании
    Director director; // директор который привязан к компании

public:
    // создание компании
    Company() : name("NULL") {}
    Company(const std::string &name, Director director) : name(name), director(director) {}

    // методы для управления компанией и директором
    Director &getDirector();
    void displayInfo() const;
    void setName(std::string name);
    std::string getName() const;
};

#endif // COMPANY_H