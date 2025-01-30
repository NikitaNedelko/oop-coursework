#include "classes/Date.h"
#include <ctime>   // Для time и localtime
#include <iomanip> // Для setw и setfill

// Конструктор по умолчанию
Date::Date()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    isLeapYear = 0;
    daysInMonth = 31;
    this->day = now->tm_mday;
    this->month = now->tm_mon + 1;
    this->year = now->tm_year + 1900;
}

// Конструктор с параметрами
Date::Date(int day, int month, int year)
{
    isLeapYear = 0;
    daysInMonth = 31;
    setYear(year);
    setMonth(month);
    setDay(day);
}

// Метод для установки года
void Date::setYear(const int &_year)
{
    validateYear(_year);
    if (_year % 4 == 0 && _year % 100 != 0 || _year % 400 == 0 && _year % 100 == 0)
        isLeapYear = 1;
    year = _year;
}

// Метод для установки месяца
void Date::setMonth(const int &_month)
{
    validateMonth(_month);
    switch (_month)
    {
    case 2:
        daysInMonth = isLeapYear ? 29 : 28;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        daysInMonth = 30;
        break;
    default:
        daysInMonth = 31;
        break;
    }
    month = _month;
}

// Метод для установки дня
void Date::setDay(const int &_day)
{
    validateDay(_day);
    day = _day;
}

// Метод для получения строки даты
std::string Date::toStringDate() const
{
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << day << "."
        << std::setw(2) << std::setfill('0') << month << "."
        << year;
    return oss.str();
}

// Оператор сравнения
bool Date::operator==(const Date &other) const
{
    return day == other.day && month == other.month && year == other.year;
}

// Вспомогательный метод для проверки года
void Date::validateYear(const int &_year)
{
    if (_year < 1970 || _year > 2026)
        throw std::invalid_argument("Неверно задан год " + std::to_string(_year));
}

// Вспомогательный метод для проверки месяца
void Date::validateMonth(const int &_month)
{
    if (_month > 12 || _month < 1)
        throw std::invalid_argument("Неверно задан месяц");
}

// Вспомогательный метод для проверки дня
void Date::validateDay(const int &_day)
{
    if (_day < 1 || _day > daysInMonth)
        throw std::invalid_argument("Неверно задан день");
}

// Геттеры для получения значений
int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}

int Date::getIsLeapYear() const
{
    return isLeapYear;
}

int Date::getDaysInMonth() const
{
    return daysInMonth;
}