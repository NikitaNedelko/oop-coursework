#ifndef SECRETARY_H
#define SECRETARY_H

#include <vector>
#include <string>
#include <map>
#include "Person.h"
#include "structs/personal_data.h"
#include "structs/meeting.h"
#include "enums/position.h"
#include "utils/enum_to_string.h"

// класс Secretary, наследуемый от Person
class Secretary : public Person
{
private:
    PersonalData personalData;

    std::vector<Meeting> meetings; // Работник и Место_встречи -> Время_встречи

public:
    Secretary(const PersonalData &personalData);

    // Геттеры и сеттеры для полей Human
    void setFirstName(const std::string &firstName) override;
    std::string getFirstName() const override;
    void setLastName(const std::string &lastName) override;
    std::string getLastName() const override;
    void setMiddleName(const std::string &middleName) override;
    std::string getMiddleName() const override;
    void setSalary(double salary) override;
    double getSalary() const override;

    // создание встречи
    void scheduleMeeting(std::vector<Person *> employees, const std::string &place, const Date &date);
    // вывод всех встреч
    std::vector<Meeting> &listScheduledMeetings();
    void displayMeetings() const;
    // вывод в таблицу
    void displayEmployeeListInTable(const std::map<Person *, Position> &employees) const;
    // вывод информации одной встречи
    void participantsOfMeeting(Meeting meeting) const;
    // вся информация о классе
    void displayInfo() const;
};

#endif // SECRETARY_H