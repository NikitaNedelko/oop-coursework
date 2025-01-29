#ifndef MEETING_H
#define MEETING_H

#include <vector>
#include <string>
#include "person.h"
#include "date.h"

// информация о встрече
struct Meeting
{
    std::vector<Person *> employees;
    std::string place;
    Date date;

    Meeting(const std::vector<Person *> &emp, const std::string &p, const Date &d)
        : employees(emp), place(p), date(d) {}
};

#endif // MEETING_H