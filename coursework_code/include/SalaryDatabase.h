#ifndef SALARY_DATABASE_H
#define SALARY_DATABASE_H

#include <map>
#include <string>
#include "enums/position.h"

class Director;

// класс для работы с минимальной ЗП и назначения ЗП на разные должности
class SalaryDatabase
{
private:
    std::map<Position, double> salaryCoefficients; // Хранение коэффициентов по должностям
    double minimumWage;                            // Минимальный размер оплаты труда

public:
    SalaryDatabase();
    SalaryDatabase(const double &minWage);

    void setCoefficient(const Position &position, const double &newCoefficient,
                        Director &director);             // назначения коэффициента зарплаты
    double getMinimalSalary(Position position) const;    // получения итоговой зарплаты для должности
    void printSalaryInfo() const;                        // вывод информации по каждой должности
    std::map<Position, double> &getSalaryCoefficients(); // возвращает список коэффициентов по каждой должности
};

#endif // SALARY_DATABASE_H