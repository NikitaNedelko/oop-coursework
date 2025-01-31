#include "classes/SalaryDatabase.h"
#include "classes/Director.h"

SalaryDatabase::SalaryDatabase() : minimumWage(19242)
{
    // Инициализация коэффициентов для должностей
    salaryCoefficients[Position::Driver] = 1.5;
    salaryCoefficients[Position::Director] = 3.5;
    salaryCoefficients[Position::SecurityGuard] = 1.2;
    salaryCoefficients[Position::Secretary] = 1.8;
    salaryCoefficients[Position::Accountant] = 2.0;
}

SalaryDatabase::SalaryDatabase(const double &minWage) : minimumWage(minWage)
{
    // Инициализация коэффициентов для должностей
    salaryCoefficients[Position::Driver] = 1.5;
    salaryCoefficients[Position::Director] = 3.5;
    salaryCoefficients[Position::SecurityGuard] = 1.2;
    salaryCoefficients[Position::Secretary] = 1.8;
    salaryCoefficients[Position::Accountant] = 2.0;
}

void SalaryDatabase::setCoefficient(const Position &position, const double &newCoefficient,
                                    Director &director)
{
    if (newCoefficient > 5)
        throw std::invalid_argument("Коэффициент больше 5 нельзя поставить");
    double oldCoefficient = salaryCoefficients[position];

    // Обновляем коэффициент зарплаты для указанной должности
    salaryCoefficients[position] = newCoefficient;

    // Пересчитываем минимальную зарплату по данной должности
    double newBaseSalary = minimumWage * newCoefficient;

    // Обновляем зарплаты сотрудников с указанной должностью и корректируем бюджет
    for (const auto &[employee, empPosition] : director.getEmployees())
    {
        if (empPosition == position)
        {
            double currentRate = employee->getSalary() / (oldCoefficient * minimumWage);
            double newSalary = newBaseSalary * currentRate;

            // Получаем текущий бюджет отдела
            double &departmentBudget = director.getApprovedBudget()[Department(int(empPosition))];

            // Проверяем, хватает ли бюджета для пересчета зарплаты
            double currentSalary = employee->getSalary();
            double salaryDifference = newSalary - currentSalary;

            if (departmentBudget - salaryDifference < 0)
                throw std::invalid_argument("Недостаточно бюджета для обновления зарплаты сотрудника " +
                                            employee->getMiddleName() + ' ' + employee->getFirstName() +
                                            ' ' + employee->getLastName() + '\n');

            // Обновляем зарплату и бюджет
            employee->setSalary(newSalary);
            departmentBudget -= salaryDifference;
        }
    }
}

double SalaryDatabase::getMinimalSalary(Position position) const
{
    return minimumWage * salaryCoefficients.at(position);
}

void SalaryDatabase::printSalaryInfo() const
{
    std::cout << "МРОТ = " << minimumWage << " руб.";
    for (const auto &entry : salaryCoefficients)
    {
        std::cout << "Должность: " << static_cast<int>(entry.first)
                  << " | Коэффициент зарплаты: " << entry.second
                  << " | Итоговая зарплата: " << getMinimalSalary(entry.first) << std::endl;
    }
}

std::map<Position, double> &SalaryDatabase::getSalaryCoefficients() { return salaryCoefficients; }
