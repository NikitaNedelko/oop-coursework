#ifndef DATE_H
#define DATE_H

#include <string>

class Date
{
public:
    // Конструктор по умолчанию
    Date();

    // Конструктор с параметрами
    Date(int day, int month, int year);

    // Методы для установки значений
    void setYear(const int &_year);
    void setMonth(const int &_month);
    void setDay(const int &_day);

    // Геттеры для получения значений
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getIsLeapYear() const;
    int getDaysInMonth() const;

    // Метод для получения строки даты
    std::string toStringDate() const;

    // Оператор сравнения
    bool operator==(const Date &other) const;

private:
    int day, month, year, isLeapYear, daysInMonth;

    // Вспомогательные методы
    void validateYear(const int &_year);
    void validateMonth(const int &_month);
    void validateDay(const int &_day);
};

#endif // DATE_H