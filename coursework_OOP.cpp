#include <algorithm>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Driver;
class Company;
class Director;
class Accountant;
class Secretary;
class SecurityGuard;
class SalaryDatabase;

class Person // базовый класс Человек
{
public:
    // свойства
    virtual void setFirstName(const string &firstName) = 0;   // Изменить имя
    virtual string getFirstName() const = 0;                  // Получить имя
    virtual void setLastName(const string &lastName) = 0;     // Изменить отчество
    virtual string getLastName() const = 0;                   // Получить отчество
    virtual void setMiddleName(const string &middleName) = 0; // Изменить фамилию
    virtual string getMiddleName() const = 0;                 // Получить фамилию
    virtual void setSalary(const double salary) = 0;          // Изменить ЗП
    virtual double getSalary() const = 0;                     // Получить ЗП

    virtual ~Person() = default;
};

struct PersonalData // персональная информация
{
    string firstName;
    string lastName;
    string middleName;
    double salary;
};

struct Date // для хранения даты
{
    int day, month, year, isLeapyYear, daysInMonth;

    Date()
    {
        time_t t = time(nullptr);
        tm *now = localtime(&t);

        isLeapyYear = 0;
        daysInMonth = 31;

        this->day = now->tm_mday;
        this->month = now->tm_mon + 1;
        this->year = now->tm_year + 1900;
    };

    Date(int day, int month, int year)
    {
        isLeapyYear = 0;
        daysInMonth = 31;

        setYear(year);
        setMonth(month);
        setDay(day);
    }

    void setYear(const int &_year)
    {
        if (_year < 1970 || _year > 2025)
            throw invalid_argument("Неверно задан год \n");
        if (_year % 4 == 0 && _year % 100 != 0 || _year % 400 == 0 && _year % 100 == 0)
            isLeapyYear = 1;
        year = _year;
    }

    void setMonth(const int &_month)
    {
        if (_month > 12 || _month < 1)
            throw invalid_argument("Неверно задан месяц");
        switch (_month)
        {
        case 2:
            daysInMonth = isLeapyYear ? 29 : 28;
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

    void setDay(const int &_day)
    {
        if (_day < 1 || _day > daysInMonth)
            throw invalid_argument("Неверно задан день");
        day = _day;
    }

    string toStringDate() const
    {
        ostringstream oss;
        oss << setw(2) << setfill('0') << day << "."
            << setw(2) << setfill('0') << month << "."
            << year;
        return oss.str();
    }

    bool operator==(const Date &other) const
    {
        return day == other.day && month == other.month && year == other.year;
    }
};

struct Meeting // информация о встрече
{
    vector<Person *> employees;
    string place;
    Date date;

    Meeting(const vector<Person *> &emp, const string &p, const Date &d) : employees(emp), place(p), date(d) {}
};

struct Trip
{
    Date dateStart;     // Дата начала поездки
    string destination; // Место назначения
};

enum class Position // должность
{
    Driver,        // водитель
    Secretary,     // секретарь
    SecurityGuard, // охранник
    Accountant,    // бухгалтер
    Director       // директор
};

enum class Department // названия отделов
{
    Transportation, // отдел транспорта     Driver
    Management,     // управление           Secretary
    Security,       // отдел безопасности   SecurityGuard
    Finance,        // финансовый отдел     Accountant
    Executive,      // исполнительный отдел Director
    Bonuses         // бюджет на премии
};

enum class Equipment
{
    Baton,      // дубинка
    Taser,      // электрошокер
    Handcuffs,  // наручники
    Flashlight, // фонарик
    PepperSpray // перечный спрей
};

// Перечисление типов водительских прав
enum class DriverLicense
{
    CATEGORY_A,
    CATEGORY_B,
    CATEGORY_C,
    CATEGORY_D,
    CATEGORY_E,
    COUNT
};

// Перечисление типов транспорта
enum class VehicleType
{
    MOTORCYCLE,
    CAR,
    TRUCK,
    BUS,
    VAN,
    COUNT
};

string toStringEnum(Position position) // функция для получения строкового представления должности
{
    switch (position)
    {
    case Position::Driver:
        return "Водитель";
    case Position::Director:
        return "Директор";
    case Position::SecurityGuard:
        return "Охранник";
    case Position::Secretary:
        return "Секретарь";
    case Position::Accountant:
        return "Бухгалтер";
    default:
        return "Неизвестная должность"; // На всякий случай
    }
}
string toStringEnum(Equipment equipment) // Функция для получения строкового представления оборудования
{
    switch (equipment)
    {
    case Equipment::Baton:
        return "Дубинка";
    case Equipment::Taser:
        return "Шокер";
    case Equipment::Handcuffs:
        return "Наручники";
    case Equipment::Flashlight:
        return "Фонарь";
    case Equipment::PepperSpray:
        return "Перцовый баллончик";
    default:
        return "Неизвестно";
    }
}
string toStringEnum(VehicleType vehicle) // Функция для конвертации типа транспорта в строку
{
    switch (vehicle)
    {
    case VehicleType::MOTORCYCLE:
        return "Мотоцикл";
    case VehicleType::CAR:
        return "Легковой автомобиль";
    case VehicleType::TRUCK:
        return "Грузовик";
    case VehicleType::BUS:
        return "Автобус";
    case VehicleType::VAN:
        return "Фургон";
    default:
        return "Неизвестный тип транспорта";
    }
}
string toStringEnum(Department department) // Функция для получения строкового представления отдела
{
    switch (department)
    {
    case Department::Transportation:
        return "Отдел транспорта";
    case Department::Management:
        return "Отдел управление";
    case Department::Security:
        return "Отдел безопасности";
    case Department::Finance:
        return "Финансовый отдел";
    case Department::Executive:
        return "Исполнит. отдел";
    case Department::Bonuses:
        return "Бюджет на премии";
    default:
        return "Неизвестный отдел";
    }
}
string toStringEnum(DriverLicense license) // функция для получения строкового представления категории водительской лицензии
{
    switch (license)
    {
    case DriverLicense::CATEGORY_A:
        return "Категория A";
    case DriverLicense::CATEGORY_B:
        return "Категория B";
    case DriverLicense::CATEGORY_C:
        return "Категория C";
    case DriverLicense::CATEGORY_D:
        return "Категория D";
    case DriverLicense::CATEGORY_E:
        return "Категория E";
    default:
        return "Неизвестная категория лицензии";
    }
}

// класс для работы с минимальной ЗП и назначения ЗП на разные должности
class SalaryDatabase
{
private:
    map<Position, double> salaryCoefficients; // Хранение коэффициентов по должностям
    double minimumWage;                       // Минимальный размер оплаты труда
public:
    SalaryDatabase() : minimumWage(19242)
    {
        // Инициализация коэффициентов для должностей
        salaryCoefficients[Position::Driver] = {1.5};
        salaryCoefficients[Position::Director] = {3.5};
        salaryCoefficients[Position::SecurityGuard] = {1.2};
        salaryCoefficients[Position::Secretary] = {1.8};
        salaryCoefficients[Position::Accountant] = {2.0};
    }
    SalaryDatabase(const double &minWage) : minimumWage(minWage)
    {
        // Инициализация коэффициентов для должностей
        salaryCoefficients[Position::Driver] = {1.5};
        salaryCoefficients[Position::Director] = {3.5};
        salaryCoefficients[Position::SecurityGuard] = {1.2};
        salaryCoefficients[Position::Secretary] = {1.8};
        salaryCoefficients[Position::Accountant] = {2.0};
    }

    // void setMinimumWage(double newMinWage);                                                                    // изменения минимальной зарплаты
    // void updateSalaries(const map<Person *, Position> &employees);                                   // обновление ЗП каждого сотрудника с учетом прошлой ставки
    void setCoefficient(const Position &position, const double &newCoefficient, Director &director); // назначения коэффициента зарплаты
    double getMinimalSalary(Position position) const;                                                // получения итоговой зарплаты для должности
    void printSalaryInfo() const;                                                                    // вывод информации по каждой должности
    map<Position, double> &getSalaryCoefficients();                                                  // возвращает список коэффициентов по каждой должности
};

// void SalaryDatabase::setMinimumWage(double newMinWage)
// {
//     minimumWage = newMinWage;
// }

double SalaryDatabase::getMinimalSalary(Position position) const
{
    return minimumWage * salaryCoefficients.at(position);
}

void SalaryDatabase::printSalaryInfo() const
{
    cout << "МРОТ = " << minimumWage << " руб.";
    for (const auto &entry : salaryCoefficients)
    {
        cout << "Должность: " << static_cast<int>(entry.first)
             << " | Коэффициент зарплаты: " << entry.second
             << " | Итоговая зарплата: " << getMinimalSalary(entry.first) << endl;
    }
}

map<Position, double> &SalaryDatabase::getSalaryCoefficients()
{
    return salaryCoefficients;
}

// класс Директор, наследуемый от Person
class Director : public Person
{
private:
    PersonalData personalData;

    SalaryDatabase salaryDatabase;             // Ссылка на базу зарплат
    map<Person *, Position> employees;         // Человек -> Должность
    map<Department, double> departmentBudgets; // Название отдела -> бюджет

public:
    Director()
    {
        setFirstName("NULL");
        setMiddleName("NULL");
        setLastName("NULL");
        setSalary(salaryDatabase.getMinimalSalary(Position::Director));
        approveBudget(Department::Bonuses, 20000);
        approveBudget(Department::Finance, 200000);
        approveBudget(Department::Management, 200000);
        approveBudget(Department::Security, 200000);
        approveBudget(Department::Transportation, 200000);
        approveBudget(Department::Executive, 100000 - getSalary());
    }

    Director(const PersonalData &personalData, SalaryDatabase &salaryDatabase) : salaryDatabase(salaryDatabase)
    {
        setFirstName(personalData.firstName);
        setMiddleName(personalData.middleName);
        setLastName(personalData.lastName);
        setSalary(salaryDatabase.getMinimalSalary(Position::Director));
        approveBudget(Department::Bonuses, 20000);
        approveBudget(Department::Finance, 200000);
        approveBudget(Department::Management, 200000);
        approveBudget(Department::Security, 200000);
        approveBudget(Department::Transportation, 200000);
        approveBudget(Department::Executive, 100000 - getSalary());
    }

    // Геттеры и сеттеры для полей Director
    void setFirstName(const string &firstName) override
    {
        personalData.firstName = firstName;
    }

    string getFirstName() const override
    {
        return personalData.firstName;
    }

    void setLastName(const string &lastName) override
    {
        personalData.lastName = lastName;
    }

    string getLastName() const override
    {
        return personalData.lastName;
    }

    void setMiddleName(const string &middleName) override
    {
        personalData.middleName = middleName;
    }

    string getMiddleName() const override
    {
        return personalData.middleName;
    }

    void setSalary(const double salary) override
    {
        personalData.salary = salary;
    }

    double getSalary() const override
    {
        return personalData.salary;
    }

    map<Person *, Position> getEmployees() const;                    // список сотрудников в подчинении -
    void approveBudget(const Department &department, double budget); // задать бюджет на отдел -
    map<Department, double> &getApprovedBudget();                    // получить бюджет отдела -
    void hireEmployee(Person *employee, const Position &position);   // нанять работника -
    void terminateEmployee(Person *employee);                        // уволить работника -
    SalaryDatabase &getSalaryDataBase();                             // получение базы данных зарплат -
    void displayInfo();                                              // вся информация о классе -
    Person *findAccountant() const;                                  // находим бухгалтера среди работников -
    Person *findSecretary() const;                                   // находим секретаря среди работников -
};

map<Person *, Position> Director::getEmployees() const
{
    return employees;
}

void Director::approveBudget(const Department &department, double budget)
{
    departmentBudgets[department] = budget;
}

map<Department, double> &Director::getApprovedBudget()
{
    return departmentBudgets;
}

void Director::hireEmployee(Person *employee, const Position &position)
{
    double baseSalary = salaryDatabase.getMinimalSalary(position);
    double currentBudget = departmentBudgets[Department(int(position))];

    // Проверяем бюджет: нужен бюджет хотя бы на минимальную ставку 0.1
    if (currentBudget < baseSalary * 0.1)
        throw invalid_argument("Недостаточно бюджета для найма на минимальную ставку");

    // установка ставки
    double maxRate = currentBudget / baseSalary;
    if (maxRate > 1.0)
        maxRate = 1.0;
    if (maxRate < 0.1)
        throw invalid_argument("Бюджета недостаточно даже для минимальной ставки.");

    employee->setSalary(baseSalary * maxRate);

    // установка начальной ставки и обновление бюджета
    employees[employee] = position;
    departmentBudgets[Department(int(position))] -= baseSalary * maxRate;

    cout << toStringEnum(position) << ' ' << employee->getMiddleName() << " нанят на работу. "
         << "C зарплатой " << employee->getSalary() << endl;
}

void Director::terminateEmployee(Person *employee)
{
    // Проверяем, что сотрудник существует в списке
    auto it = employees.find(employee);
    if (it == employees.end())
        throw invalid_argument("Сотрудник не найден.");

    // Получаем позицию и зарплату сотрудника
    Position position = it->second;
    double salary = employee->getSalary();

    // Возвращаем зарплату в бюджет отдела
    departmentBudgets[Department(int(position))] += salary;

    cout << "Сотрудник " << employee->getMiddleName() << " уволен. Бюджет отдела " << toStringEnum(Department(int(position))) << " восстановлен на " << salary << "\n";

    // Удаляем сотрудника из списка
    employees.erase(it);
    delete employee;
}

SalaryDatabase &Director::getSalaryDataBase()
{
    return salaryDatabase;
}

void Director::displayInfo()
{
    cout << left << setw(3) << "№ |"
         << setw(10) << "Должность|"
         << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
         << "  Зарплата   |" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(13, '-') << '+' << endl;

    cout << left << setw(2) << 0
         << setw(10) << "|" + toStringEnum(Position::Director)
         << setw(16) << "|" + getMiddleName()
         << setw(16) << "|" + getFirstName()
         << setw(16) << "|" + getLastName()
         << "|" << fixed << setprecision(2) << getSalary() << " руб.|" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(13, '-') << '+' << endl;

    cout << "\nБюджет отделов:\n";
    for (auto &department : getApprovedBudget())
    {
        cout << setw(20) << toStringEnum(department.first) // Название отдела
             << setw(7) << department.second               // Бюджет
             << " руб." << endl;
    }
}

Person *Director::findAccountant() const
{
    for (const auto &employee : employees)
        if (employee.second == Position::Accountant)
            return employee.first; // Возвращаем указатель на бухгалтера
    return nullptr;                // Бухгалтер не найден
}

Person *Director::findSecretary() const
{
    for (const auto &employee : employees)
        if (employee.second == Position::Secretary)
            return employee.first; // Возвращаем указатель на секретаря
    return nullptr;                // секретарь не найден
}

void SalaryDatabase::setCoefficient(const Position &position, const double &newCoefficient, Director &director)
{
    if (newCoefficient > 5)
        throw invalid_argument("Коэффициент больше 5 нельзя поставить");
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
                throw invalid_argument("Недостаточно бюджета для обновления зарплаты сотрудника " + employee->getMiddleName() + ' ' + employee->getFirstName() + ' ' + employee->getLastName() + '\n');

            // Обновляем зарплату и бюджет
            employee->setSalary(newSalary);
            departmentBudget -= salaryDifference;
        }
    }
}

// класс Бухгалтер, наследуемый от Person
class Accountant : public Person
{
private:
    PersonalData personalData;

    SalaryDatabase salaryDatabase;          // Ссылка на базу зарплат
    map<Person *, double> employeesRate;    // Хранение ставки по каждому сотруднику
    map<Person *, double> employeesBonuses; // Хранение премиальных по каждому сотруднику

public:
    Accountant(const PersonalData &personalData, SalaryDatabase &salaryDatabase) : salaryDatabase(salaryDatabase)
    {
        setFirstName(personalData.firstName);
        setMiddleName(personalData.middleName);
        setLastName(personalData.lastName);
        setSalary(salaryDatabase.getMinimalSalary(Position::Accountant));
    }

    // Геттеры и сеттеры для полей Accountant
    void setFirstName(const string &firstName) override
    {
        personalData.firstName = firstName;
    }

    string getFirstName() const override
    {
        return personalData.firstName;
    }

    void setLastName(const string &lastName) override
    {
        personalData.lastName = lastName;
    }

    string getLastName() const override
    {
        return personalData.lastName;
    }

    void setMiddleName(const string &middleName) override
    {
        personalData.middleName = middleName;
    }

    string getMiddleName() const override
    {
        return personalData.middleName;
    }

    void setSalary(double salary) override
    {
        personalData.salary = salary;
    }

    double getSalary() const override
    {
        return personalData.salary;
    }

    void applyBonuses(Person *employee, const double bonus, Director &director); // изменение премии сотрудников
    void setRate(Person *employee, double rate, Director &director);             // изменение ставки сотрудников
    void updateEmployeesRate(Director &director);                                // добавление ставок сотрудников в массив ставок
    double getEmployeeRate(Person *employee) const;                              // получение ставки сотрудника
    double getEmployeeBonus(Person *employee) const;                             // получение премии сотрудника
    SalaryDatabase &getSalaryDataBase();                                         // выводим базу данных зарплат
    Position getEmployeeType(Person *employee);                                  // определяем что за работник относительно Person *
    map<Person *, double> getEmployeesRates() const;                             // все ставки по каждому сотруднику
    void displayInfo();                                                          // вся информация о классе
};

void Accountant::applyBonuses(Person *employee, double bonus, Director &director)
{
    if (bonus < 100 && bonus > 0)
        throw invalid_argument("Премия не может быть меньше 100 рублей");
    if (bonus > employee->getSalary())
        throw invalid_argument("Премия не может быть больше оклада");

    double currentBudgetBonuses = director.getApprovedBudget()[Department::Bonuses] + getEmployeeBonus(employee);

    if (bonus > currentBudgetBonuses)
        throw invalid_argument("Недостаточно бюджета для выдачи премий!");

    director.approveBudget(Department::Bonuses, currentBudgetBonuses - bonus); // изменение бюджета бонусов
    employeesBonuses[employee] = bonus;
    cout << "Изменена премия для " << employee->getMiddleName() << ' ' << employee->getFirstName() << " " << employee->getLastName() << " на " << fixed << setprecision(2) << employeesBonuses[employee] << " руб." << endl;
}

void Accountant::updateEmployeesRate(Director &director)
{
    for (const auto &[employee, position] : director.getEmployees())
    {
        // Проверяем, есть ли уже ставка для сотрудника
        if (employeesRate.find(employee) != employeesRate.end())
            continue;
        setRate(employee, employee->getSalary() / salaryDatabase.getMinimalSalary(position), director);
    }
}

void Accountant::setRate(Person *employee, double newRate, Director &director)
{
    // Проверка минимальной ставки
    if (newRate < 0.1)
        throw invalid_argument("Ставка не может быть ниже 0.1.");

    Position position = getEmployeeType(employee);

    // Получение базовой зарплаты и текущего бюджета отдела
    double baseSalary = salaryDatabase.getMinimalSalary(position);
    double currentBudget = director.getApprovedBudget()[Department(int(position))];

    // Проверка, что сотрудник существует в базе ставок
    auto it = employeesRate.find(employee);
    if (it != employeesRate.end()) // если сотрудник найден (старый)
    {
        double oldRate = it->second; // Текущая ставка сотрудника
        double oldSalary = baseSalary * oldRate;
        // Рассчитываем изменение бюджета
        double newSalary = baseSalary * newRate;
        double salaryDifference = newSalary - oldSalary;
        if (salaryDifference > 0 && currentBudget < salaryDifference)
            throw invalid_argument("Недостаточно бюджета для увеличения ставки. " + to_string(salaryDifference - currentBudget) + " руб.\n");
        // Обновление ставки и бюджета отдела
        employeesRate[employee] = newRate;
        director.getApprovedBudget()[Department(int(position))] -= salaryDifference;
        employee->setSalary(newSalary);

        cout << "Ставка сотрудника " << employee->getMiddleName() << " изменена на " << newRate
             << ". Зарплата теперь " << employee->getSalary() << ".\n";
        return;
    }

    // Обновление ставки и бюджета отдела
    employeesRate[employee] = newRate;

    return;
}

double Accountant::getEmployeeRate(Person *employee) const
{
    return employeesRate.at(employee);
}

double Accountant::getEmployeeBonus(Person *employee) const
{
    auto it = employeesBonuses.find(employee);
    if (it != employeesBonuses.end())
    {
        return it->second;
    }
    return 0; // Возвращаем 0, если ключ не найден
}

map<Person *, double> Accountant::getEmployeesRates() const
{
    return employeesRate;
}

SalaryDatabase &Accountant::getSalaryDataBase()
{
    return salaryDatabase;
}

void Accountant::displayInfo()
{ // Заголовок таблицы
    cout << left << setw(3) << "№ |"
         << setw(10) << "Должность|"
         << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
         << "   Зарплата   |" << setw(6) << "Ставка|" << "    Премия    |" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
         << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-')
         << '+' << string(6, '-') << '+' << string(14, '-') << '+' << endl;

    // Данные о бухгалтере
    cout << left << setw(2) << 0
         << setw(10) << "|" + toStringEnum(Position::Accountant)
         << setw(16) << "|" + getMiddleName()
         << setw(16) << "|" + getFirstName()
         << setw(16) << "|" + getLastName()
         << "|" << setw(9) << fixed << setprecision(2) << getSalary() << " руб.|"
         << setw(6) << fixed << setprecision(2) << getEmployeeRate(this) << "|"
         << setw(9) << fixed << setprecision(2) << getEmployeeBonus(this) << " руб.|" << endl;

    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-')
         << '+' << string(15, '-') << '+' << string(15, '-') << '+'
         << string(14, '-') << '+' << string(6, '-') << '+' << string(14, '-') << '+' << endl;
}

// класс Secretary, наследуемый от Person
class Secretary : public Person
{
private:
    PersonalData personalData;

    vector<Meeting> meetings; // Работник и Место_встречи -> Время_встречи

public:
    Secretary(const PersonalData &personalData)
    {
        setFirstName(personalData.firstName);
        setMiddleName(personalData.middleName);
        setLastName(personalData.lastName);
    }

    // Геттеры и сеттеры для полей Human
    void setFirstName(const string &firstName) override
    {
        personalData.firstName = firstName;
    }

    string getFirstName() const override
    {
        return personalData.firstName;
    }

    void setLastName(const string &lastName) override
    {
        personalData.lastName = lastName;
    }

    string getLastName() const override
    {
        return personalData.lastName;
    }

    void setMiddleName(const string &middleName) override
    {
        personalData.middleName = middleName;
    }

    string getMiddleName() const override
    {
        return personalData.middleName;
    }

    void setSalary(double salary) override
    {
        personalData.salary = salary;
    }

    double getSalary() const override
    {
        return personalData.salary;
    }

    // методы планирования встреч и управления данными о сотрудниках
    void scheduleMeeting(vector<Person *> employees, const string &place, const Date &date); /// создание встречи
    vector<Meeting> &listScheduledMeetings();
    void displayMeetings() const;                                                    // вывод всех встреч
    void displayEmployeeListInTable(const map<Person *, Position> &employees) const; // вывод в таблицу
    void participantsOfMeeting(Meeting meeting) const;                               // вывод информации одной встречи
    void displayInfo() const;                                                        // вся информация о классе
};

void Secretary::displayEmployeeListInTable(const map<Person *, Position> &employees) const
{
    int employeeNumber = 1;
    for (int i = 0; i <= 4; ++i)
    {
        for (const auto &pair : employees)
        {
            Person *employee = pair.first;
            string positionName = toStringEnum(pair.second);

            if (i == 1 && pair.second == Position::Accountant ||
                i == 2 && pair.second == Position::Secretary ||
                i == 3 && pair.second == Position::Driver ||
                i == 4 && pair.second == Position::SecurityGuard)
            {
                cout << fixed << setprecision(2);
                cout << left << setw(2) << employeeNumber++
                     << setw(10) << "|" + positionName
                     << setw(16) << "|" + employee->getMiddleName()
                     << setw(16) << "|" + employee->getFirstName()
                     << setw(16) << "|" + employee->getLastName()
                     << "|" << setw(9) << fixed << setprecision(2) << employee->getSalary() << " руб.|" << endl;
                cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;
            }
        }
    }
}

void Secretary::scheduleMeeting(vector<Person *> employees, const string &place, const Date &date)
{
    // Проверка на количество встреч за текущий день
    int meetingsToday = 0;

    // Проверка на участие сотрудника в другой встрече в то же время
    for (const auto &meeting : meetings)
    {
        if (meeting.date == date)
        {
            meetingsToday++;
            if (meetingsToday == 5)
                throw("Нельзя запланировать больше 5 встреч за день\n");
            for (const auto &employee : employees)
            {
                if (find(meeting.employees.begin(), meeting.employees.end(), employee) != meeting.employees.end())
                {
                    system("cls");
                    cout << "Сотрудник " << employee->getMiddleName() << " " << employee->getFirstName() << " уже занят на встрече в это время.\n";
                    system("pause");
                    return;
                }
            }
        }
    }

    // Если все условия выполнены, добавляем встречу
    meetings.emplace_back(employees, place, date);
    cout << "Встреча успешно запланирована.\n";
}

vector<Meeting> &Secretary::listScheduledMeetings()
{
    return meetings;
}

void Secretary::displayMeetings() const
{
    cout << "Запланированные встречи:\n\n";
    int index = 0;
    for (const auto &meeting : meetings)
    {
        cout << ++index << ") Место: " << meeting.place << ", Дата: " << meeting.date.toStringDate() << "\n";
        // cout << "Сотрудники: ";
        // for (const auto &emp : meeting.employees)
        // {
        //     cout << emp->getFirstName() << " " << emp->getMiddleName();
        // }
    }
}

void Secretary::participantsOfMeeting(Meeting meeting) const
{
    cout << "Место: " << meeting.place << ", Дата: " << meeting.date.toStringDate() << "\n";
    cout << "Сотрудники: \n";
    for (const auto &emp : meeting.employees)
    {
        cout << emp->getMiddleName() << " " << emp->getFirstName() << " " << emp->getLastName() << endl;
    }
    cout << "\n";
}

void Secretary::displayInfo() const
{

    cout << left << setw(3) << "№ |"
         << setw(10) << "Должность|"
         << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
         << "   Зарплата   |" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

    cout << left << setw(2) << 0
         << setw(10) << "|" + toStringEnum(Position::Secretary)
         << setw(16) << "|" + getMiddleName()
         << setw(16) << "|" + getFirstName()
         << setw(16) << "|" + getLastName()
         << "|" << setw(9) << fixed << setprecision(2) << getSalary() << " руб.|" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;
}

// класс SecurityGuard, наследуемый от Person
class SecurityGuard : public Person
{
private:
    PersonalData personalData;

    map<string, string> locations; // Место -> Статус проверки
    Equipment specialEquipment;    // Название спецсредства (дубинка, шокер и т.д.)

    // Список всех объектов
    vector<string> departments = {"Склад", "Производство", "Администрация", "Лаборатория"};
    // Список возможных статусов
    vector<string> statuses = {"Всё в порядке", "Нужна проверка", "Нарушение безопасности", "Неизвестный статус"};

public:
    SecurityGuard(const PersonalData &personalData, const Equipment &equipment) : specialEquipment(equipment)
    {
        setFirstName(personalData.firstName);
        setMiddleName(personalData.middleName);
        setLastName(personalData.lastName);
        specialEquipment = Equipment::Flashlight;
        for (string dep : departments)
        {
            locations[dep] = "Нужна проверка";
        }
    }
    // Геттеры и сеттеры для полей Human
    void setFirstName(const string &firstName) override
    {
        personalData.firstName = firstName;
    }

    string getFirstName() const override
    {
        return personalData.firstName;
    }

    void setLastName(const string &lastName) override
    {
        personalData.lastName = lastName;
    }

    string getLastName() const override
    {
        return personalData.lastName;
    }

    void setMiddleName(const string &middleName) override
    {
        personalData.middleName = middleName;
    }

    string getMiddleName() const override
    {
        return personalData.middleName;
    }

    void setSalary(double salary) override
    {
        personalData.salary = salary;
    }

    double getSalary() const override
    {
        return personalData.salary;
    }

    // методы проверки безопасности и составления отчетов об инцидентах
    void setSecurityStatus(string &department, string &status); // Метод для изменения статуса безопасности
    void generateIncidentReport() const;                        // Метод для генерации отчета о безопасности
    void setSpecialEquipment(const Equipment equipment);
    Equipment getSpecialEquipment() const;
    vector<string> allDepartments(); // все объекты
    vector<string> allStatuses();    // все статусы
    void displayInfo() const;        // вся информация о классе
};

vector<string> SecurityGuard::allDepartments()
{
    return departments;
}
vector<string> SecurityGuard::allStatuses()
{
    return statuses;
}
void SecurityGuard::setSecurityStatus(string &department, string &status)
{
    locations[department] = status;
}
void SecurityGuard::generateIncidentReport() const
{
    cout << "\nОтчет о безопасности:\n";
    cout << "Отдел\t\tСтатус\n";
    cout << "--------------------------------------------------------\n";
    int i = 0;
    for (const auto &location : locations)
    {
        cout << ++i << ") " << location.first << "\t" << location.second << endl;
    }
}
void SecurityGuard::setSpecialEquipment(const Equipment equipment)
{
    specialEquipment = equipment;
}
Equipment SecurityGuard::getSpecialEquipment() const
{
    return specialEquipment;
}
void SecurityGuard::displayInfo() const
{
    cout << left << setw(3) << "№ |"
         << setw(10) << "Должность|"
         << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
         << "   Зарплата   |" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

    cout << left << setw(2) << 0
         << setw(10) << "|" + toStringEnum(Position::SecurityGuard)
         << setw(16) << "|" + getMiddleName()
         << setw(16) << "|" + getFirstName()
         << setw(16) << "|" + getLastName()
         << "|" << setw(9) << fixed << setprecision(2) << getSalary() << " руб.|" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

    cout << "Спец средство: " << toStringEnum(getSpecialEquipment());
}

// класс Driver, наследуемый от Person
class Driver : public Person
{
private:
    PersonalData personalData;

    string destination;
    vector<DriverLicense> licenseCategories; // Массив категорий прав (например, A, B, C)
    vector<VehicleType> vehicles;            // Массив транспортных средств, которыми управляет водитель
    vector<string> cities;

public:
    Driver(const PersonalData &personalData, DriverLicense licenseCategories, VehicleType vehicles)
    {
        setFirstName(personalData.firstName);
        setMiddleName(personalData.middleName);
        setLastName(personalData.lastName);
        addLicenseCategory(licenseCategories);
        addVehicle(vehicles);
        destination = "Не задано";
        cities = {"Москва", "Санкт-Петербург", "Нижний Новгород", "Казань", "Челябинск", "Омск", "Ростов-на-Дону", "Уфа", "Не задано"};
    }
    // Геттеры и сеттеры для полей Human
    void setFirstName(const string &firstName) override
    {
        personalData.firstName = firstName;
    }

    string getFirstName() const override
    {
        return personalData.firstName;
    }

    void setLastName(const string &lastName) override
    {
        personalData.lastName = lastName;
    }

    string getLastName() const override
    {
        return personalData.lastName;
    }

    void setMiddleName(const string &middleName) override
    {
        personalData.middleName = middleName;
    }

    string getMiddleName() const override
    {
        return personalData.middleName;
    }

    void setSalary(double salary) override
    {
        personalData.salary = salary;
    }

    double getSalary() const override
    {
        return personalData.salary;
    }

    void changeDestination(const string &newDestination);   // новое место назначение
    const vector<string> getCities();                       // список городов (доступных мест назначений)
    void addLicenseCategory(const DriverLicense &category); // Метод для добавления категории водительских прав
    vector<DriverLicense> &getLicenseCategories();          // Метод для получения категории водительских прав
    void addVehicle(const VehicleType &vehicle);            // Метод для добавления транспортного средства
    vector<VehicleType> &getVehicles();                     // Метод вывода всех транспортных средств
    void displayInfo() const;                               // отображение всей информации класса
};

void Driver::addLicenseCategory(const DriverLicense &category)
{
    licenseCategories.push_back(category);
}
void Driver::addVehicle(const VehicleType &vehicle)
{
    vehicles.push_back(vehicle);
}
void Driver::changeDestination(const string &newDestination)
{
    destination = newDestination;
}
vector<DriverLicense> &Driver::getLicenseCategories()
{
    return licenseCategories;
}
vector<VehicleType> &Driver::getVehicles()
{
    return vehicles;
}
void Driver::displayInfo() const
{
    cout << left << setw(3) << "№ |"
         << setw(10) << "Должность|"
         << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
         << "   Зарплата   |" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

    cout << left << setw(2) << 0
         << setw(10) << "|" + toStringEnum(Position::Driver)
         << setw(16) << "|" + getMiddleName()
         << setw(16) << "|" + getFirstName()
         << setw(16) << "|" + getLastName()
         << "|" << setw(9) << fixed << setprecision(2) << getSalary() << " руб.|" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

    if (!licenseCategories.empty())
    {
        cout << "Имеющиеся категории прав : ";
        for (DriverLicense dl : licenseCategories)
        {
            cout << toStringEnum(dl) << " ";
        }
        cout << endl;
    }
    cout << endl;

    if (!vehicles.empty())
    {
        cout << "Имеющиеся транспортные средства : ";
        for (VehicleType vt : vehicles)
        {
            cout << toStringEnum(vt) << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Выехал в город - " << destination;
    cout << endl;
}
const vector<string> Driver::getCities()
{
    return cities;
}

Position Accountant::getEmployeeType(Person *employee) // определяем что за работник относительно Person *
{
    if (dynamic_cast<Driver *>(employee))
        return Position::Driver;
    else if (dynamic_cast<SecurityGuard *>(employee))
        return Position::SecurityGuard;
    else if (dynamic_cast<Director *>(employee))
        return Position::Director;
    else if (dynamic_cast<Accountant *>(employee))
        return Position::Accountant;
    else if (dynamic_cast<Secretary *>(employee))
        return Position::Secretary;

    throw invalid_argument("Неизвестный тип работника");
}

class Company // класс для управления компанией
{
private:
    string name;       // название компании
    Director director; // директор который привязан к компании

public:
    // создание компании
    Company() : name("NULL") {}
    Company(const string &name, Director director) : name(name), director(director) {}

    // методы для управления компанией и директором
    Director &getDirector();
    void displayInfo() const;
    void setName(string name);
    string getName() const;
};

Director &Company::getDirector()
{
    return director;
}

void Company::displayInfo() const
{
    cout << "Название компании: " << name << endl;
    cout << "Директор: " << director.getFirstName() << " " << director.getLastName() << endl;
    cout << "Зарплата: " << director.getSalary() << " руб." << endl;
}
void Company::setName(string name)
{
    this->name = name;
}
string Company::getName() const
{
    return name;
}

// ------------------------MENU------------------------

class Menu
{
private:
    int choice;
    vector<Company> companies; // список всех компаний

public:
    // ------------------------manualInput------------------------
    // определяем что за работник относительно Person *
    Position getEmployeeType(Person *employee) // получение типа сотрудника по объекту Person *
    {
        if (dynamic_cast<Driver *>(employee))
            return Position::Driver;
        else if (dynamic_cast<SecurityGuard *>(employee))
            return Position::SecurityGuard;
        else if (dynamic_cast<Director *>(employee))
            return Position::Director;
        else if (dynamic_cast<Accountant *>(employee))
            return Position::Accountant;
        else if (dynamic_cast<Secretary *>(employee))
            return Position::Secretary;

        throw invalid_argument("Неизвестный тип работника");
    }

    void displayAllEmployees(Director &director, vector<Person *> &employees) // вывод всех сотрудников в таблицу (должность, ФИО, ЗП)
    {
        int employeeNumber = 1;
        for (int i = 0; i <= 4; ++i)
        {
            for (const auto &pair : director.getEmployees())
            {
                Person *employee = pair.first;
                string positionName = toStringEnum(pair.second);

                if (i == 1 && pair.second == Position::Accountant ||
                    i == 2 && pair.second == Position::Secretary ||
                    i == 3 && pair.second == Position::Driver ||
                    i == 4 && pair.second == Position::SecurityGuard)
                {
                    cout << fixed << setprecision(2);
                    cout << left << setw(2) << employeeNumber++
                         << setw(10) << "|" + positionName
                         << setw(16) << "|" + employee->getMiddleName()
                         << setw(16) << "|" + employee->getFirstName()
                         << setw(16) << "|" + employee->getLastName()
                         << "|" << setw(9) << fixed << setprecision(2) << employee->getSalary() << " руб.|" << endl;
                    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;
                    employees.push_back(employee);
                }
            }
        }
    }
    void displayAllEmployeesWithInt(Director &director, vector<int> &indexs) // вывод определенного сотрудника в таблицу (должность, ФИО, ЗП)
    {
        int employeeNumber = 1;
        for (int i = 0; i <= 4; ++i)
        {
            for (const auto &pair : director.getEmployees())
            {
                Person *employee = pair.first;
                string positionName = toStringEnum(pair.second);

                if (i == 1 && pair.second == Position::Accountant ||
                    i == 2 && pair.second == Position::Secretary ||
                    i == 3 && pair.second == Position::Driver ||
                    i == 4 && pair.second == Position::SecurityGuard)
                {
                    if (find(indexs.begin(), indexs.end(), employeeNumber) != indexs.end())
                    {
                        employeeNumber++;
                        continue;
                    }
                    cout << fixed << setprecision(2);
                    cout << left << setw(2) << employeeNumber++
                         << setw(10) << "|" + positionName
                         << setw(16) << "|" + employee->getMiddleName()
                         << setw(16) << "|" + employee->getFirstName()
                         << setw(16) << "|" + employee->getLastName()
                         << "|" << setw(9) << fixed << setprecision(2) << employee->getSalary() << " руб.|" << endl;
                    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;
                }
            }
        }
    }
    void displayAllEmployeesWithRatesAndBonuses(Director &director, Accountant &accountant) // вывод всех сотрудников в таблицу (должность, ФИО, ЗП, ставка, премия)
    {
        clearConsole();
        cout << left << setw(3) << "№ |"
             << setw(10) << "Должность|"
             << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
             << "   Зарплата   |" << setw(6) << "Ставка|" << setw(14) << "    Премии    |" << endl;
        cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
             << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-')
             << '+' << string(6, '-') << '+' << string(14, '-') << '+' << endl;
        // Вывод информации о директоре
        cout << left << setw(2) << 0
             << setw(10) << "|" + toStringEnum(Position::Director)
             << setw(16) << "|" + director.getMiddleName()
             << setw(16) << "|" + director.getFirstName()
             << setw(16) << "|" + director.getLastName()
             << "|" << setw(9) << fixed << setprecision(2) << director.getSalary() << " руб.|"
             << setw(6) << "1.00  |"
             << setw(9) << fixed << setprecision(2) << accountant.getEmployeeBonus(&director) << " руб.|" << endl;
        cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-')
             << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-')
             << '+' << string(6, '-') << '+' << string(14, '-') << '+' << endl;

        // Переменная для нумерации сотрудников
        int employeeNumber = 1;

        for (int i = 0; i <= 4; ++i)
        {
            for (const auto &pair : director.getEmployees())
            {
                Person *employee = pair.first;
                string positionName = toStringEnum(pair.second);

                // Вывод информации в зависимости от должности
                if (i == 1 && pair.second == Position::Accountant ||
                    i == 2 && pair.second == Position::Secretary ||
                    i == 3 && pair.second == Position::Driver ||
                    i == 4 && pair.second == Position::SecurityGuard)
                {
                    cout << fixed << setprecision(2);
                    cout << left << setw(2) << employeeNumber++
                         << setw(10) << "|" + positionName
                         << setw(16) << "|" + employee->getMiddleName()
                         << setw(16) << "|" + employee->getFirstName()
                         << setw(16) << "|" + employee->getLastName()
                         << "|" << setw(9) << fixed << setprecision(2) << employee->getSalary() << " руб.|"
                         << setw(6) << fixed << setprecision(2) << accountant.getEmployeeRate(employee) << "|"
                         << setw(9) << fixed << setprecision(2) << accountant.getEmployeeBonus(employee) << " руб.|" << endl;

                    // Разделитель для строк
                    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-')
                         << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-')
                         << '+' << string(6, '-') << '+' << string(14, '-') << '+' << endl;
                }
            }
        }
    }
    void displayAllEmployeesWithRates(Director &director, Accountant &accountant, vector<Person *> &employees) // вывод всех сотрудников в таблицу (должность, ФИО, ЗП, ставка)
    {
        // Переменная для нумерации сотрудников
        int employeeNumber = 1;

        for (int i = 0; i <= 4; ++i)
        {
            for (const auto &pair : director.getEmployees())
            {
                Person *employee = pair.first;
                string positionName = toStringEnum(pair.second);

                // Вывод информации в зависимости от должности
                if (i == 1 && pair.second == Position::Accountant ||
                    i == 2 && pair.second == Position::Secretary ||
                    i == 3 && pair.second == Position::Driver ||
                    i == 4 && pair.second == Position::SecurityGuard)
                {
                    cout << fixed << setprecision(2);
                    cout << left << setw(2) << employeeNumber++
                         << setw(10) << "|" + positionName
                         << setw(16) << "|" + employee->getMiddleName()
                         << setw(16) << "|" + employee->getFirstName()
                         << setw(16) << "|" + employee->getLastName()
                         << "|" << setw(9) << fixed << setprecision(2) << employee->getSalary() << " руб.|"
                         << setw(6) << fixed << setprecision(2) << accountant.getEmployeeRate(employee) << "|" << endl;

                    // Разделитель для строк
                    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
                         << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-')
                         << '+' << string(6, '-') << '+' << endl;
                    employees.push_back(employee);
                }
            }
        }
    }
    void displayAllEmployeesWithBonuses(Director &director, Accountant &accountant, vector<Person *> &employees) // вывод всех сотрудников в таблицу (должность, ФИО, ЗП, премия)
    {
        // Переменная для нумерации сотрудников
        int employeeNumber = 1;

        for (int i = 0; i <= 4; ++i)
        {
            for (const auto &pair : director.getEmployees())
            {
                Person *employee = pair.first;
                string positionName = toStringEnum(pair.second);

                // Вывод информации в зависимости от должности
                if (i == 1 && pair.second == Position::Accountant ||
                    i == 2 && pair.second == Position::Secretary ||
                    i == 3 && pair.second == Position::Driver ||
                    i == 4 && pair.second == Position::SecurityGuard)
                {
                    cout << fixed << setprecision(2);
                    cout << left << setw(2) << employeeNumber++
                         << setw(10) << "|" + positionName
                         << setw(16) << "|" + employee->getMiddleName()
                         << setw(16) << "|" + employee->getFirstName()
                         << setw(16) << "|" + employee->getLastName()
                         << "|" << setw(9) << fixed << setprecision(2) << employee->getSalary() << " руб."
                         << "|" << setw(9) << fixed << setprecision(2) << accountant.getEmployeeBonus(employee) << " руб.|" << endl;

                    // Разделитель для строк
                    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
                         << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-')
                         << '+' << string(14, '-') << '+' << endl;
                    employees.push_back(employee);
                }
            }
        }
    }
    void displayALLPositionsWithKoef(Accountant &accountant) // вывод всех должностей их коэффициент и зарплату
    {
        SalaryDatabase &salaryDatabase = accountant.getSalaryDataBase(); // Получаем базу данных зарплат
        // Заголовок таблицы
        cout << left << setw(2) << "№ |"
             << setw(10) << "Должность|"
             << setw(11) << "Коэффициент|"
             << "   Зарплата   |" << endl;
        cout << string(2, '-') << '+' << string(9, '-') << '+' << string(11, '-') << '+' << string(14, '-') << '+' << endl;

        // Вывод данных
        const auto &coefficients = salaryDatabase.getSalaryCoefficients(); // Предполагается, что метод возвращает данные по должностям

        int i = 1;
        for (const auto &[position, coefficient] : coefficients)
        {
            cout << left << setw(2) << i << "|"
                 << setw(9) << toStringEnum(position) << "|"
                 << setw(11) << fixed << setprecision(2) << coefficient << "|"
                 << setw(9) << fixed << setprecision(2) << salaryDatabase.getMinimalSalary(position) << " руб.|" << endl;

            // Линия-разделитель после каждой строки данных
            cout << string(2, '-') << '+' << string(9, '-') << '+' << string(11, '-') << '+' << string(14, '-') << '+' << endl;
            ++i;
        }
    }

    vector<Company> getListOfCompanies() const // получение массива компаний
    {
        return companies;
    }
    bool createCompanyManually(Company &company) // создание компании в ручную
    {
        clearConsole();

        string companyName;
        cout << "Введите название компании: ";
        if (!inputString(companyName, 2, 15))
            return 0;
        clearConsole();

        string firstName;
        cout << "Введите имя директора: ";
        if (!inputString(firstName, 2, 15))
            return 0;
        clearConsole();

        string middleName;
        cout << "Введите фамилию директора: ";
        if (!inputString(middleName, 2, 15))
            return 0;
        clearConsole();

        string lastName;
        cout << "Введите отчество директора: ";
        if (!inputString(lastName, 2, 15))
            return 0;
        clearConsole();

        Director director;
        director.setFirstName(firstName);
        director.setLastName(lastName);
        director.setMiddleName(middleName);
        Company temp(companyName, director);
        company = temp;
        return 1;
    }
    bool changeNameCompany(Company &Company) // изменение названия компании
    {
        clearConsole();

        string companyName;
        cout << "Введите новое название компании: ";
        if (!inputString(companyName, 2, 15))
            return 0;
        clearConsole();
        Company.setName(companyName);
        cout << "Новое имя компании " << '\"' << companyName << '\"' << " успешно задано \n";
        return 0;
    }
    bool deleteCompany(Company &companyToRemove) // удаление компании
    {
        clearConsole();

        // Удаление компании из вектора `companies`
        for (auto it = companies.begin(); it != companies.end();)
        {
            if (&(*it) == &companyToRemove) // Проверяем адрес, чтобы найти нужную компанию
            {
                it = companies.erase(it); // Удаляем компанию и обновляем итератор
                cout << "Компания успешно удалена.\n";
                break;
            }
            else
            {
                ++it;
            }
        }

        system("pause");
        return 0;
    }

    bool setFIO(Person &person) // изменение ФМО сотрудника
    {
        clearConsole();
        string firstName;
        cout << "Введите имя: ";
        if (!inputString(firstName, 2, 15))
            return 0;
        clearConsole();

        string middleName;
        cout << "Введите фамилию: ";
        if (!inputString(middleName, 2, 15))
            return 0;
        clearConsole();

        string lastName;
        cout << "Введите отчество: ";
        if (!inputString(lastName, 2, 15))
            return 0;
        clearConsole();

        person.setFirstName(firstName);
        person.setLastName(lastName);
        person.setMiddleName(middleName);
        return 1;
    }
    bool hireEmployeeMenu(Director &director) // меню нанять на работу от лица директора, с выбором должности нового рабочего, ввода ФИО  (проверка что бухгалтер и секретарь уже есть в компании и что бюджета отдела хватит на найм рабочего)
    {
        clearConsole();
        Accountant *acc = dynamic_cast<Accountant *>(director.findAccountant());
        Secretary *sec = dynamic_cast<Secretary *>(director.findSecretary());
        // Список доступных должностей для найма
        vector<Position> availablePositions = {Position::Driver, Position::Secretary, Position::SecurityGuard, Position::Accountant};

        cout << "Выберите тип работника для найма:\n";
        for (size_t i = 0; i < availablePositions.size(); ++i)
            cout << i + 1 << ". " << toStringEnum(availablePositions[i]) << endl;

        if (!inputSingleInt(choice, 1, 4))
            return 0;

        Position selectedPosition = availablePositions[choice - 1];

        // Проверка на уникальные должности (бухгалтер и секретарь )
        if ((acc != nullptr && selectedPosition == Position::Accountant) || (sec != nullptr && selectedPosition == Position::Secretary))
            throw invalid_argument("Такой работник уже нанят");

        // Создаем новый объект сотрудника в зависимости от выбранной позиции
        Person *newEmployee = nullptr;
        PersonalData pd;
        switch (selectedPosition)
        {
        case Position::Driver:
        {
            DriverLicense dl = generateRandomDriverLicense();
            newEmployee = new Driver(pd, dl, generateRandomVehicle(dl));
            break;
        }
        case Position::Secretary:
            newEmployee = new Secretary(pd);
            break;
        case Position::SecurityGuard:
            newEmployee = new SecurityGuard(pd, generateRandomSpecialEquipment());
            break;
        case Position::Accountant:
            newEmployee = new Accountant(pd, director.getSalaryDataBase());
            break;
        default:
            cout << "Ошибка: Неверная должность.\n";
            return false;
        }
        if (!setFIO(*newEmployee))
            return 0;
        try
        {
            // Нанимаем сотрудника с выбранной позицией
            director.hireEmployee(newEmployee, selectedPosition);
            Accountant *acc = dynamic_cast<Accountant *>(director.findAccountant());
            if (acc != nullptr)
                acc->updateEmployeesRate(director);
            system("pause");
            return true;
        }
        catch (const invalid_argument &e)
        {
            cout << "Ошибка при найме сотрудника: " << e.what() << endl;
            delete newEmployee; // Освобождаем память, если сотрудник не был нанят
            system("pause");
            return false;
        }
    }
    bool terminateEmployeeMenu(Director &director) // меню выбора сотрудника на увольнение (ЗП сотрудника возвращается в бюджет отдела)
    {
        clearConsole();

        // Получаем всех работников из директора
        map<Person *, Position> employees = director.getEmployees();

        // Проверяем, есть ли сотрудники для увольнения
        if (employees.empty())
        {
            cout << "Нет сотрудников для увольнения.\n";
            system("pause");
            return false;
        }

        // Отображаем всех сотрудников с их должностями
        cout << "Список сотрудников:\n\n";

        vector<Person *> employeeList;

        cout << left << setw(3) << "№ |"
             << setw(10) << "Должность|"
             << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
             << "  Зарплата   |" << endl;
        cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(13, '-') << '+' << endl;

        displayAllEmployees(director, employeeList);

        // Получаем выбор пользователя
        cout
            << "Введите номер сотрудника, которого хотите уволить: ";
        int choice;
        if (!inputInt(choice, 1, employeeList.size()))
            return 0;

        // Выбор сотрудника и увольнение
        Person *employeeToFire = employeeList[choice - 1];
        try
        {
            clearConsole();
            director.terminateEmployee(employeeToFire); // Удаление сотрудника из map в директоре
            system("pause");
            return true;
        }
        catch (const exception &e)
        {
            cout << "Ошибка при увольнении сотрудника: " << e.what() << endl;
            return false;
        }
    }

    bool createMeeting(Secretary &secretary, Director &director) //  создание встреч. Задается время, название, участники и место встречи
    {
        clearConsole();
        // Ввод названия комнаты
        string roomName;
        cout << "Введите название комнаты для встречи: ";
        if (!inputString(roomName, 2, 5, 0, 1))
            return 0;
        clearConsole();

        // Ввод даты встречи
        int day, month, year;
        cout << "Введите год проведения встречи : ";
        if (!inputInt(year, 2024, 2025))
            return 0;

        Date meetingDate;
        meetingDate.setYear(year);
        clearConsole();

        cout << "Введите месяц проведения встречи : ";
        if (!inputInt(month, 1, 12))
            return 0;
        meetingDate.setMonth(month);
        clearConsole();

        cout << "Введите день проведения встречи : ";
        if (!inputInt(day, 1, 31))
            return 0;
        meetingDate.setDay(day);
        clearConsole();

        // после выбора сотрудников опять выводим

        vector<Person *> listEmployees;

        vector<Person *> employees;

        displayAllEmployees(director, employees);

        vector<int> selectedEmployeeNumbers;

        while (true)
        {
            clearConsole();
            if (selectedEmployeeNumbers.size() == employees.size())
            {
                cout << "все сотрудники добавлены на встречу";
                system("pause");
                break;
            }
            cout << left << setw(3) << "№ |"
                 << setw(10) << "Должность|"
                 << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
                 << "   Зарплата   |" << endl;
            cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

            if (find(selectedEmployeeNumbers.begin(), selectedEmployeeNumbers.end(), 0) == selectedEmployeeNumbers.end())
            {
                cout << left << setw(2) << 0
                     << setw(10) << "|" + toStringEnum(Position::Director)
                     << setw(16) << "|" + director.getMiddleName()
                     << setw(16) << "|" + director.getFirstName()
                     << setw(16) << "|" + director.getLastName()
                     << "|" << setw(9) << fixed << setprecision(2) << director.getSalary() << " руб.|" << endl;
                cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;
            }

            displayAllEmployeesWithInt(director, selectedEmployeeNumbers);

            cout << "Выберите сотрудника для назначения на встречу: ";

            if (!inputInt(choice, 0, director.getEmployees().size()))
                break;
            ;

            if (find(selectedEmployeeNumbers.begin(), selectedEmployeeNumbers.end(), choice) != selectedEmployeeNumbers.end())
            {
                continue;
            }

            selectedEmployeeNumbers.push_back(choice);

            if (choice == 0)
            {
                listEmployees.push_back(&director);
            }
            else if (choice <= director.getEmployees().size())
            {
                listEmployees.push_back(employees[choice - 1]);
            }
            else
            {
                throw("Неверный индекс выбора персонала на встречу\n");
            }

            // clearConsole();

            // cout << "Хотите добавить еще сотрудника на встречу ?\n";
            // cout << "1. Да\n";
            // cout << "2. Нет\n\n";
            // if (!inputSingleInt(choice, 1, 2))
            //     return 0;

            // if (choice == 1)
            //     continue;
            // else
            // {
            //     break;
            // }
            // Создание встречи
        }
        clearConsole();
        if (!selectedEmployeeNumbers.empty())
        {
            secretary.scheduleMeeting(listEmployees, roomName, meetingDate);
        }
        return 0;
    }
    bool getParticipantOfMeeting(Secretary &secretary) // вывод всех созданных встреч
    {
        vector<Meeting> listOfMeeting = secretary.listScheduledMeetings();
        clearConsole();
        if (listOfMeeting.empty())
        {
            cout << "Список встреч пуст\n";
            system("pause");
            return 0;
        }
        secretary.displayMeetings();
        cout << endl;
        if (!inputSingleInt(choice, 1, listOfMeeting.size()))
            return 0;
        clearConsole();

        int i = 1;
        for (Meeting meeting : listOfMeeting)
        {
            if (i == choice)
                secretary.participantsOfMeeting(meeting);
            i++;
        }
        system("pause");
        return 0;
    }
    bool deleteMeeting(Secretary &secretary) // выбор встречи для удаление
    {
        vector<Meeting> &listOfMeeting = secretary.listScheduledMeetings();
        clearConsole();
        if (listOfMeeting.empty())
        {
            cout << "Список встреч пуст\n";
            system("pause");
            return 0;
        }
        secretary.displayMeetings();
        cout << endl;
        if (!inputSingleInt(choice, 1, listOfMeeting.size()))
            return 0;
        clearConsole();

        int i = 1;
        for (Meeting meeting : listOfMeeting)
        {
            if (i == choice)
                listOfMeeting.erase(listOfMeeting.begin() + choice - 1);
            i++;
        }
        cout << "Встреча успешно удалена\n";
        system("pause");
        return 0;
    }
    // ------------------------RANDOM------------------------
    // Функция для генерации случайного имени
    string generateRandomFirstName() const
    {
        const vector<string> firstNames = {"Никита", "Алексей", "Андрей", "Александр", "Дмитрий", "Даниил"};
        return firstNames[rand() % firstNames.size()];
    }
    // Функция для генерации случайной фамилии
    string generateRandomMiddleName() const
    {
        const vector<string> middlenames = {"Иванов", "Смирнов ", "Кузнецов", "Попов", "Васильев", "Петров", "Соколов", "Михайлов", "Новиков", "Федоров", "Морозов", "Волков", "Алексеев", "Лебедев", "Семенов", "Егоров", "Павлов", "Козлов", "Степанов", "Николаев"};
        return middlenames[rand() % middlenames.size()];
    }
    // Функция для генерации случайного отчества
    string generateRandomLastName() const
    {
        const vector<string> lastNames = {"Владимирович", "Александрович", "Николаевич", "Сергеевич", "Викторович", "Анатольевич", "Иванович", "Юрьевич", "Михайлович", "Алексеевич", "Петрович", "Станиславович", "Григорьевич", "Дмитриевич", "Никитич", "Станиславович", "Алексиевич", "Евгеньевич", "Тимофеевич", "Матвеевич"};
        return lastNames[rand() % lastNames.size()];
    }
    // Функция для генерации случайного названия компании
    string generateRandomCompanyName() const
    {
        const vector<string> companyNames = {
            "ТехноЛаб", "ИнноваСофт", "ПроектГрупп", "ЭкспертСистем", "ДельтаТек",
            "ГлобалСервис", "ЭкоТек", "СуперМаркет", "АльфаКорп", "БетаМедиа"};
        return companyNames[rand() % companyNames.size()];
    }
    // Функция для генерации случайного специального оборудования
    Equipment generateRandomSpecialEquipment()
    {
        return static_cast<Equipment>(rand() % 5); // 5 - количество типов оборудования
    }
    // Функция для генерации случайного города
    string generateRandomCity()
    {
        const vector<string> cities = {"Москва", "Санкт-Петербург", "Новосибирск", "Екатеринбург", "Нижний Новгород", "Казань", "Челябинск", "Омск", "Ростов-на-Дону", "Уфа"};
        return cities[rand() % cities.size()];
    }
    // Функция для генерации случайной даты в диапазоне от сегодня до года вперед
    Date generateRandomDate()
    {
        Date today;

        // случайное количество дней от 0 до 364
        int randomDays = rand() % 365;

        tm tmDate = {};
        tmDate.tm_year = today.year - 1900;
        tmDate.tm_mon = today.month - 1;
        tmDate.tm_mday = today.day;

        time_t currentTime = mktime(&tmDate);

        currentTime += randomDays * 24 * 3600;

        tm *randomTm = localtime(&currentTime);

        return Date(randomTm->tm_mday, randomTm->tm_mon + 1, randomTm->tm_year + 1900);
    }
    // Функция для генерации случайной комнаты
    string generateRandomRoom()
    {
        vector<string> rooms = {"Зал для совещаний", "Конференц-зал", "Студия", "Аудитория 12", "Лаунж зона", "Кабинета 4", "Выставочный зал", "Тренинговый центр", "Зал для презентаций", "Зал для банкетов"};

        int randomIndex = rand() % rooms.size();
        return rooms[rand() % rooms.size()];
    }
    // Функция для генерации случайного типа прав для водителя
    DriverLicense generateRandomDriverLicense()
    {
        return static_cast<DriverLicense>(rand() % static_cast<int>(DriverLicense::COUNT));
    }
    // Функция для генерации случайного транспорта в зависимости от типа прав
    VehicleType generateRandomVehicle(const DriverLicense &license)
    {
        switch (license)
        {
        case DriverLicense::CATEGORY_A:
            return VehicleType::MOTORCYCLE; // Для категории A
        case DriverLicense::CATEGORY_B:
            return VehicleType::CAR; // Для категории B
        case DriverLicense::CATEGORY_C:
            return VehicleType::TRUCK; // Для категории C
        case DriverLicense::CATEGORY_D:
            return VehicleType::BUS; // Для категории D
        case DriverLicense::CATEGORY_E:
            return VehicleType::VAN; // Для категории E
        default:
            return VehicleType::CAR; // По умолчанию
        }
    }

    // Функция для создания компании с рандомными значениями
    Company createCompanyRandom()
    {
        clearConsole();
        SalaryDatabase salaryDatabase(19242); // МРОТ по Москве
        PersonalData pd;
        DriverLicense dl;
        VehicleType vt;
        Equipment equipment;

        pd.firstName = generateRandomCompanyName();
        pd.firstName = generateRandomFirstName();
        pd.middleName = generateRandomMiddleName();
        pd.lastName = generateRandomLastName();
        Director director(pd, salaryDatabase); // Директор

        pd.firstName = generateRandomCompanyName();
        pd.firstName = generateRandomFirstName();
        pd.middleName = generateRandomMiddleName();
        pd.lastName = generateRandomLastName();
        Accountant *accountant = new Accountant(pd, salaryDatabase); // Бухгалтер
        director.hireEmployee(accountant, Position::Accountant);

        pd.firstName = generateRandomCompanyName();
        pd.firstName = generateRandomFirstName();
        pd.middleName = generateRandomMiddleName();
        pd.lastName = generateRandomLastName();
        Secretary *secretary = new Secretary(pd); // Секретарь
        // secretary->setSalary(director.getSalaryDataBase().getMinimalSalary(Position::Secretary));
        director.hireEmployee(secretary, Position::Secretary);

        pd.firstName = generateRandomCompanyName();
        pd.firstName = generateRandomFirstName();
        pd.middleName = generateRandomMiddleName();
        pd.lastName = generateRandomLastName();
        dl = generateRandomDriverLicense();
        vt = generateRandomVehicle(dl);
        Driver *driver = new Driver(pd, dl, vt); // Водитель
        // driver->setSalary(director.getSalaryDataBase().getMinimalSalary(Position::Driver));
        director.hireEmployee(driver, Position::Driver);

        pd.firstName = generateRandomCompanyName();
        pd.firstName = generateRandomFirstName();
        pd.middleName = generateRandomMiddleName();
        pd.lastName = generateRandomLastName();
        dl = generateRandomDriverLicense();
        vt = generateRandomVehicle(dl);
        Driver *driver2 = new Driver(pd, dl, vt); // Водитель
        // driver2->setSalary(director.getSalaryDataBase().getMinimalSalary(Position::Driver));
        director.hireEmployee(driver2, Position::Driver);

        pd.firstName = generateRandomCompanyName();
        pd.firstName = generateRandomFirstName();
        pd.middleName = generateRandomMiddleName();
        pd.lastName = generateRandomLastName();
        equipment = generateRandomSpecialEquipment();
        SecurityGuard *securityGuard = new SecurityGuard(pd, equipment); // Охранник
        // securityGuard->setSalary(director.getSalaryDataBase().getMinimalSalary(Position::SecurityGuard));
        director.hireEmployee(securityGuard, Position::SecurityGuard);

        pd.firstName = generateRandomCompanyName();
        pd.firstName = generateRandomFirstName();
        pd.middleName = generateRandomMiddleName();
        pd.lastName = generateRandomLastName();
        equipment = generateRandomSpecialEquipment();
        SecurityGuard *securityGuard2 = new SecurityGuard(pd, equipment); // Охранник
        // securityGuard2->setSalary(director.getSalaryDataBase().getMinimalSalary(Position::SecurityGuard));
        director.hireEmployee(securityGuard2, Position::SecurityGuard);

        // создание встреч
        vector<Person *> emp;
        emp.push_back(securityGuard2);
        emp.push_back(securityGuard);
        emp.push_back(secretary);
        vector<Person *> emp2;
        emp2.push_back(accountant);
        emp2.push_back(driver2);
        emp2.push_back(driver);
        secretary->scheduleMeeting(emp, generateRandomRoom(), generateRandomDate());
        secretary->scheduleMeeting(emp2, generateRandomRoom(), generateRandomDate());

        accountant->updateEmployeesRate(director);
        return Company(generateRandomCompanyName(), director);
    }

    // ------------------------UI------------------------
    bool inputSingleInt(int &digit, const int start, const int end);                                                              // ввод положительной цифры
    bool inputString(string &str, const int &minLen = 2, const int &maxLen = 15, bool firstBigLetter = 1, bool allowNumbers = 0); // ввод строки
    bool inputInt(int &number, const int &min = INT_MIN / 10, const int &max = INT_MAX / 10,
                  const string &key = "NULL", const bool minus = 0, const bool point = 0); // ввод числа int
    bool inputDouble(double &number, const double &min = __DBL_MIN__ / 10, const double &max = __DBL_MAX__ / 10,
                     const string &key = "NULL", const bool minus = 0, const bool point = 1, int decimalLimit = 2); // ввод double
    void clearConsole();                                                                                            // очистка консоли и вывод сообщения "нажмите esc чтобы выйти"

    // ------------------------MENU------------------------
    // меню создания компании
    bool createCompanyMenu()
    {
        clearConsole();

        if (companies.size() >= 9)
            throw invalid_argument("Максимальное количество компаний");

        cout << "Меню создания компании" << '\n';
        cout << "1. Создать компанию вручную\n";
        cout << "2. Создать компанию с случайными значениями\n";

        if (!inputSingleInt(choice, 1, 2))
            return 0;

        Company company;

        switch (choice)
        {
        case 1:
            if (!createCompanyManually(company))
                return 1;
            companies.emplace_back(company);
            break;
        case 2:
            try
            {
                companies.emplace_back(createCompanyRandom());
            }
            catch (const invalid_argument &e)
            {
                cout << "ОШИБКА: " << e.what() << endl;
            }
            break;
        default:
            return 1;
        }

        cout << "Компания создана успешно:\n";
        companies[companies.size() - 1].displayInfo();
        return 0;
    }
    // меню выбора создать или управлять компаниями
    bool CompanyMenu()
    {
        clearConsole();

        cout << "Выберите действие:\n";
        cout << "1. Создать новую компанию\n";
        cout << "2. Управление компаниями\n";

        if (!inputSingleInt(choice, 1, 2))
            return 0;

        switch (choice)
        {
        case 1:
            try
            {
                while (createCompanyMenu())
                    ;
            }
            catch (const invalid_argument &e)
            {
                system("cls");
                cerr << "ОШИБКА: " << e.what() << '\n';
                system("pause");
            }
            break;
        case 2:
            while (manageCompaniesMenu())
                ;
            break;
        default:
            return 1;
        }
        return 1;
    }
    // меню выбора компании для управления
    bool manageCompaniesMenu()
    {
        clearConsole();

        if (companies.empty()) // Список компаний пуст
        {
            cout << "Список компаний пуст \n";
            system("pause");
            return 0;
        }

        int i = 0;

        for (Company company : companies) // Вывод компаний
        {
            i++;
            cout << i << ") ";
            company.displayInfo();
            cout << endl;
        }

        cout << "Какой компанией вы хотите управлять ?\n";

        if (!inputSingleInt(choice, 1, companies.size()))
            return 0;

        try
        {
            int numOfCompany = choice - 1;
            while (workWithCompany(companies[numOfCompany]))
                ;
            return 1;
        }
        catch (const invalid_argument &e)
        {
            system("cls");
            cerr << "ОШИБКА: " << e.what() << '\n';
            system("pause");
            return 1;
        }
    }
    // меню управления одной компанией
    bool workWithCompany(Company &company)
    {
        clearConsole();
        company.displayInfo();
        cout << endl;
        cout << "Список возможных функций:" << '\n'
             << "1. Изменить имя компании" << '\n'
             << "2. Перейти к управлению работников компании" << '\n'
             << "3. Удалить компанию" << '\n';

        if (!inputSingleInt(choice, 1, 3))
            return 0;

        switch (choice)
        {
        case 1: // изменение имени файла

            while (changeNameCompany(company))
                ;
            system("pause");
            return 1;
        case 2: // Перейти к управлению работников компании
            while (manageEmploeesMenu(company.getDirector()))
                ;
            return 1;
        case 3: // удалить компанию
            while (deleteCompany(company))
                ;
            return 0;
        default:
            return 1;
        }
        return 1;
    }
    // управление сотрудниками компании
    bool manageEmploeesMenu(Director &director)
    {
        clearConsole();
        cout << "Сотрудники данной компании: \n\n";

        cout << left << setw(3) << "№ |"
             << setw(10) << "Должность|"
             << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
             << "   Зарплата   |" << endl;
        cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

        cout << left << setw(2) << 0
             << setw(10) << "|" + toStringEnum(Position::Director)
             << setw(16) << "|" + director.getMiddleName()
             << setw(16) << "|" + director.getFirstName()
             << setw(16) << "|" + director.getLastName()
             << "|" << setw(9) << fixed << setprecision(2) << director.getSalary() << " руб.|" << endl;
        cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

        vector<Person *> employeeList;
        displayAllEmployees(director, employeeList);

        cout << "\nВыберите сотрудника: ";
        if (!inputInt(choice, 0, director.getEmployees().size()))
            return 0;

        if (choice == 0)
        {
            while (manageEmployeeMenu(director))
                ;
            return 1;
        }

        Person *employee = employeeList[choice - 1];
        Position pos = getEmployeeType(employee);
        try
        {
            if (pos == Position::Accountant)
                while (manageEmployeeMenu(dynamic_cast<Accountant *>(employee), director))
                    ;
            if (pos == Position::Secretary)
                while (manageEmployeeMenu(dynamic_cast<Secretary *>(employee), director))
                    ;
            if (pos == Position::Driver)
                while (manageEmployeeMenu(dynamic_cast<Driver *>(employee)))
                    ;
            if (pos == Position::SecurityGuard)
                while (manageEmployeeMenu(dynamic_cast<SecurityGuard *>(employee)))
                    ;
        }
        catch (const invalid_argument &e)
        {
            system("cls");
            cout << e.what();
            system("pause");
        }
        return 1;
    }
    // управление бюджетом отделов
    bool manageBudgetDepartmentsMenu(Director &director)
    {
        clearConsole();
        // Получаем список отделов и их текущие бюджеты
        map<Department, double> departmentBudgets = director.getApprovedBudget();

        // Список для выбора отдела
        cout << "Бюджет отделов:\n";
        int i = 1;
        vector<Department> departments;
        for (const auto &entry : departmentBudgets)
        {
            cout << i++ << ". " << toStringEnum(entry.first) << " \t(Бюджет: " << entry.second << " руб.)\n";
            departments.push_back(entry.first); // Сохраняем отдел для выбора
        }

        if (!inputSingleInt(choice, 1, departments.size()))
            return 0;

        Department selectedDepartment = departments[choice - 1];

        // Изменение бюджета выбранного отдела
        clearConsole();
        double newBudget;
        cout << "Введите новый бюджет для " << toStringEnum(selectedDepartment) << ": ";
        if (!inputDouble(newBudget, 0, 500000, "New Bonus", false, true))
            return false;
        clearConsole();
        cout << "Прошлый бюджет " << toStringEnum(selectedDepartment) << " = " << departmentBudgets[selectedDepartment] << " руб." << endl;
        director.approveBudget(selectedDepartment, newBudget);
        cout << "Нынешний бюджет " << toStringEnum(selectedDepartment) << " успешно изменен на " << newBudget << " руб.\n";
        system("pause");
        return 1;
    }
    // изменение ставок сотрудников
    bool setEmploeesRatesMenu(Accountant &accountant, Director &director)
    {
        clearConsole();
        cout << "Список сотрудников и их текущая ставка:\n\n";

        vector<Person *> employees;

        cout << left << setw(3) << "№ |"
             << setw(10) << "Должность|"
             << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
             << "   Зарплата   |" << setw(6) << "Ставка|" << endl;
        cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
             << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-')
             << '+' << string(6, '-') << '+' << endl;

        displayAllEmployeesWithRates(director, accountant, employees);

        // Запрашиваем выбор сотрудника для изменения ставки
        cout << "\nВыберите номер сотрудника для изменения ставки: ";
        if (!inputInt(choice, 1, employees.size()))
            return 0;

        // Определяем выбранного сотрудника
        Person *selectedEmployee = nullptr;
        int index = 1;
        for (const auto &emploee : employees)
        {
            if (index++ == choice)
            {
                selectedEmployee = emploee;
                break;
            }
        }
        clearConsole();
        // Ввод новой ставки для выбранного сотрудника
        cout << "Введите новую ставку для " << selectedEmployee->getMiddleName() << " "
             << selectedEmployee->getFirstName() << ": ";
        double newRate;
        if (!inputDouble(newRate, 0.001, 1.0)) // Например, диапазон ставок от 0.0 до 1.0
            return 0;

        clearConsole();
        // Обновление ставки сотрудника через бухгалтера
        accountant.setRate(selectedEmployee, newRate, director);
        system("pause");
        return true;
    }
    // изменение ставок сотрудников
    bool setEmployeesBonusesMenu(Accountant &accountant, Director &director)
    {
        clearConsole();
        cout << "Сотрудники и их премии:\n\n";

        cout << left << setw(3) << "№ |"
             << setw(10) << "Должность|"
             << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
             << "   Зарплата   |" << "    Премии    |" << endl;
        cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
             << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-')
             << '+' << string(14, '-') << '+' << endl;

        // Выводим список сотрудников и их премий
        vector<Person *> currentEmployees;

        displayAllEmployeesWithBonuses(director, accountant, currentEmployees);

        cout << "Бюджет выделенный на премии = " << fixed << setprecision(2) << director.getApprovedBudget().at(Department::Bonuses) << " руб. \n";

        cout << "\nВыберите сотрудника, которому нужно изменить премию (введите номер): ";
        if (!inputInt(choice, 1, currentEmployees.size()))
            return 0;

        clearConsole();

        // Получаем выбранного сотрудника
        auto selectedEmployee = currentEmployees[choice - 1]; // Получаем указатель на выбранного сотрудника

        double newBonus;
        cout << "Введите новую премию для работника " << selectedEmployee->getMiddleName() << " " << selectedEmployee->getFirstName() << ": ";
        if (!inputDouble(newBonus, 0, director.getApprovedBudget()[Department::Bonuses] + accountant.getEmployeeBonus(selectedEmployee), "New Bonus", false, true))
            return false;

        // Устанавливаем новую премию
        clearConsole();
        try
        {
            accountant.applyBonuses(selectedEmployee, newBonus, director);
        }
        catch (const invalid_argument &e)
        {
            cout << e.what();
        }
        system("pause");
        return true;
    }
    // изменение коэффициента должности
    bool setCoefficientMenu(Accountant &accountant, Director &director)
    {
        clearConsole();
        SalaryDatabase &salaryDatabase = accountant.getSalaryDataBase(); // Получаем базу данных зарплат

        cout << "Список должностей, их коэффициентов и ЗП:\n\n";
        const auto &coefficients = salaryDatabase.getSalaryCoefficients();

        displayALLPositionsWithKoef(accountant);

        cout << "\nБюджет отделов:\n";
        for (auto &department : director.getApprovedBudget())
        {
            cout << setw(20) << toStringEnum(department.first) // Название отдела
                 << setw(7) << department.second               // Бюджет
                 << " руб." << endl;
        }

        cout << "\nВыберите должность для изменения коэффициента\n";
        if (!inputSingleInt(choice, 1, coefficients.size()))
            return false;

        // Получаем выбранную должность
        Position selectedPosition = next(coefficients.begin(), choice - 1)->first;

        clearConsole();

        cout << "Введите новый коэффициент для должности " << toStringEnum(selectedPosition) << ": ";
        double newCoefficient;
        if (!inputDouble(newCoefficient, 0.1, 5, "null", false, true)) // Пример диапазона от 0.1 до 10
            return false;

        // Устанавливаем новый коэффициент через метод SalaryDatabase
        try
        {
            clearConsole();
            salaryDatabase.setCoefficient(selectedPosition, newCoefficient, director);
            cout << "Коэффициент для должности " << toStringEnum(selectedPosition) << " успешно изменен на "
                 << newCoefficient << ".\n";
        }
        catch (const invalid_argument &e)
        {
            cout << e.what();
        }
        system("pause");
        return true;
    }
    // меню управления встречами
    bool meetingManageMenu(Secretary &secretary, Director &director)
    {
        clearConsole();
        secretary.displayMeetings();
        cout << endl;
        cout << "Список возможных функций:" << '\n'
             << "1. Создать встречу" << '\n'
             << "2. Вывести участников встречи" << '\n'
             << "3. Удалить встречу" << '\n';

        if (!inputSingleInt(choice, 1, 3))
            return 0;

        switch (choice)
        {
        case 1: // Создать встречу

            while (createMeeting(secretary, director))
                ;
            system("pause");
            return 1;
        case 2: // Вывести участников встречи
            while (getParticipantOfMeeting(secretary))
                ;
            return 1;
        case 3: // Удалить встречу
            while (deleteMeeting(secretary))
                ;
            return 1;
        default:
            return 1;
        }
        return 1;
    }
    // меню изменения статуса отделов
    bool manageStatusLocationsMenu(SecurityGuard &securityGuard)
    {
        clearConsole();
        // Список всех объектов
        vector<string> departments = securityGuard.allDepartments();
        // Список возможных статусов
        vector<string> statuses = securityGuard.allStatuses();

        cout << "Выберите отдел для проверки статуса:\n";
        securityGuard.generateIncidentReport();
        if (!inputSingleInt(choice, 1, securityGuard.allDepartments().size()))
            return 0;

        string selectedDepartment = departments[choice - 1];
        clearConsole();
        // Выбор статуса
        cout << "\nВыберите статус для отдела " << selectedDepartment << ":\n";
        for (size_t i = 0; i < statuses.size(); ++i)
        {
            cout << i + 1 << ". " << statuses[i] << endl;
        }
        if (!inputSingleInt(choice, 1, securityGuard.allStatuses().size()))
            return 0;

        // Сохранение статуса и комментария для выбранного отдела
        securityGuard.setSecurityStatus(selectedDepartment, statuses[choice - 1]);
        cout << "Статус для отдела " << selectedDepartment << " успешно обновлен.\n";
        system("pause");
        return 1;
    }
    // меню изменения спец средств
    bool manageSpecialEquipmentMenu(SecurityGuard &securityGuard)
    {
        clearConsole();

        cout << "Выберите, какое спец. средство дать охраннику:\n";
        for (int i = 0; i < int(Equipment::PepperSpray); i++)
        {
            cout << i + 1 << ") " << toStringEnum(Equipment(i)) << '\n';
        }
        if (!inputSingleInt(choice, 1, 4))
            return 0;
        securityGuard.setSpecialEquipment(Equipment(choice - 1));
        return 0;
    }
    // меню выбора места, куда поедет водитель
    bool manageDriverDestinationMenu(Driver &driver)
    {
        clearConsole();
        cout << "Выберите город, куда отправится водитель:\n";
        int i = 1;
        for (string dest : driver.getCities())
        {
            cout << i++ << ") " << dest << endl;
        }

        if (!inputSingleInt(choice, 1, 9))
            return 0;

        driver.changeDestination(driver.getCities()[choice - 1]);

        clearConsole();
        cout << "Место назначение задано\n";
        system("pause");
        return 1;
    }
    // меню добавления/удаление водительских прав
    bool manageDriverLicenseCategoriesMenu(Driver &driver)
    {
        clearConsole();
        cout << "Выберите категории прав для добавления (введите номер категории):\n";
        for (size_t i = 0; i < int(DriverLicense::COUNT); ++i)
        {
            cout << i + 1 << ") " << toStringEnum(DriverLicense(i)) << endl;
        }

        if (!inputSingleInt(choice, 1, 5))
            return 0;

        vector<DriverLicense> &licenseCategories = driver.getLicenseCategories();

        clearConsole();

        if (find(licenseCategories.begin(), licenseCategories.end(), DriverLicense(choice - 1)) == licenseCategories.end())
        {
            driver.addLicenseCategory(DriverLicense(choice - 1));
            cout << "Категория " << toStringEnum(DriverLicense(choice - 1)) << " добавлена.\n";
        }
        else
        {
            driver.getLicenseCategories().erase(find(licenseCategories.begin(), licenseCategories.end(), DriverLicense(choice - 1)));
            vector<VehicleType> &vehicles = driver.getVehicles(); // Ссылка на транспортные средства водителя
            cout << "Категория " << toStringEnum(DriverLicense(choice - 1)) << " удалена.\n";
            auto vehicleIt = find(vehicles.begin(), vehicles.end(), VehicleType(choice - 1));
            if (vehicleIt != vehicles.end())
            {
                vehicles.erase(vehicleIt);
                cout << "Транспортное средство " << toStringEnum(VehicleType(choice - 1)) << " удалено.\n";
            }
        }
        system("pause");
        return 1;
    }
    // меню добавления/удаление транспорта
    bool manageDriverVehiclesMenu(Driver &driver)
    {
        clearConsole();

        vector<DriverLicense> &licenseCategories = driver.getLicenseCategories();

        if (licenseCategories.empty())
        {
            cout << "У водителя нет прав\n";
            system("pause");
            return 0;
        }

        vector<VehicleType> currentLC;

        int i = 1;
        for (const DriverLicense &category : licenseCategories)
        {
            cout << i++ << ") " << toStringEnum(VehicleType(int(category))) << endl;
            currentLC.push_back(VehicleType(int(category)));
        }

        // Выводим список доступных транспортных средств для выбора
        cout << "Выберите транспортное средство для добавления:\n";

        if (!inputSingleInt(choice, 1, 5))
            return 0;

        VehicleType selectedVehicle = currentLC[choice - 1];
        vector<VehicleType> &vehicles = driver.getVehicles(); // Ссылка на транспортные средства водителя

        clearConsole();

        auto vehicleIt = find(vehicles.begin(), vehicles.end(), selectedVehicle);
        if (vehicleIt == vehicles.end())
        {
            // Добавление, если транспортное средство не найдено
            vehicles.push_back(selectedVehicle);
            cout << "Транспортное средство " << toStringEnum(selectedVehicle) << " добавлено.\n";
        }
        else
        {
            // Удаление, если транспортное средство уже существует
            vehicles.erase(vehicleIt);
            cout << "Транспортное средство " << toStringEnum(selectedVehicle) << " удалено.\n";
        }

        system("pause");
        return 1;
    }

    // функции директора
    bool manageEmployeeMenu(Director &director)
    {
        clearConsole();

        director.displayInfo();
        cout << endl;
        cout << "Список возможных функций:" << '\n'
             << "1. Изменить ФИО" << '\n'
             << "2. Нанять работника" << '\n'
             << "3. Уволить работника" << '\n'
             << "4. Вывести всех работников" << '\n'
             << "5. Управление бюджетом отделов" << '\n';

        if (!inputSingleInt(choice, 1, 5))
            return 0;

        switch (choice)
        {
        case 1: // изменение ФИО
            setFIO(director);
            return 1;
        case 2: // Нанять работника
            try
            {
                while (hireEmployeeMenu(director))
                    ;
            }
            catch (const invalid_argument &e)
            {
                clearConsole();
                cout << "Ошибка при найме сотрудника: " << e.what() << endl;

                system("pause");
            }
            return 1;
        case 3: // уволить работника
            while (terminateEmployeeMenu(director))
                ;
            return 1;
        case 4: // вывести всех работников данного директора
        {
            clearConsole();
            vector<Person *> vect;

            cout << left << setw(3) << "№ |"
                 << setw(10) << "Должность|"
                 << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
                 << "  Зарплата   |" << endl;
            cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(13, '-') << '+' << endl;

            displayAllEmployees(director, vect);
            system("pause");
            return 1;
        }
        case 5: // Управление бюджетом отделов
            while (manageBudgetDepartmentsMenu(director))
                ;
            return 1;
        default:
            return 1;
        }
        return 1;
    }
    // функции бухгалтера
    bool manageEmployeeMenu(Accountant *accountant, Director &director)
    {
        clearConsole();
        accountant->displayInfo();
        cout << endl;
        cout << "Список возможных функций:" << '\n'
             << "1. Изменить ФИО" << '\n'
             << "2. Изменить ставку сотруднику " << '\n'
             << "3. Назначить премиальные сотруднику" << '\n'
             << "4. Изменить коэффициент ЗП должности" << '\n'
             << "5. Вывести информацию о всех работниках" << '\n';

        if (!inputSingleInt(choice, 1, 5))
            return 0;

        switch (choice)
        {
        case 1: // изменение ФИО
            setFIO(*accountant);
            return 1;
        case 2: // Изменить ставку сотруднику
            while (setEmploeesRatesMenu(*accountant, director))
                ;
            return 1;
        case 3: // Назначить премиальные сотруднику
            while (setEmployeesBonusesMenu(*accountant, director))
                ;
            return 1;
        case 4: // Изменить коэффициент ЗП должности
            while (setCoefficientMenu(*accountant, director))
                ;
            return 1;
        case 5: // Вывести информацию о всех работниках
            displayAllEmployeesWithRatesAndBonuses(director, *accountant);
            system("pause");
            return 1;
        default:
            return 1;
        }
        return 1;
    }
    // функции секретаря
    bool manageEmployeeMenu(Secretary *secretary, Director &director)
    {
        clearConsole();

        map<Person *, Position> securityOrDriver;

        secretary->displayInfo();
        cout << endl;
        cout << "Список возможных функций:" << '\n'
             << "1. Изменить ФИО" << '\n'
             << "2. Вывести сотрудников, данного директора" << '\n'
             << "3. Вывести данные об охранниках" << '\n'
             << "4. Вывести данные о водителях" << '\n'
             << "5. Управление встречами" << '\n';

        if (!inputSingleInt(choice, 1, 5))
            return 0;

        switch (choice)
        {
        case 1: // изменение ФИО
            setFIO(*secretary);
            return 1;
        case 2: // Вывести сотрудников, данного директора
            clearConsole();

            cout << left << setw(3) << "№ |"
                 << setw(10) << "Должность|"
                 << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
                 << "   Зарплата   |" << endl;
            cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

            secretary->displayEmployeeListInTable(director.getEmployees());
            system("pause");
            return 1;
        case 3: // Вывести данные об охранниках
            securityOrDriver.clear();
            clearConsole();

            cout << left << setw(3) << "№ |"
                 << setw(10) << "Должность|"
                 << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
                 << "   Зарплата   |" << endl;
            cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

            for (const auto pair : director.getEmployees())
            {
                if (pair.second == Position::SecurityGuard)
                    securityOrDriver[pair.first] = pair.second;
            }
            if (securityOrDriver.empty())
            {
                clearConsole();
                cout << "Сотрудников нет\n";
                system("pause");
                return 1;
            }
            secretary->displayEmployeeListInTable(securityOrDriver);
            system("pause");
            return 1;
        case 4: // Вывести данные о водителях
            securityOrDriver.clear();
            clearConsole();

            cout << left << setw(3) << "№ |"
                 << setw(10) << "Должность|"
                 << setw(45) << "    Фамилия    |      Имя      |   Отчество    |"
                 << "   Зарплата   |" << endl;
            cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

            for (const auto pair : director.getEmployees())
            {
                if (pair.second == Position::Driver)
                    securityOrDriver[pair.first] = pair.second;
            }
            if (securityOrDriver.empty())
            {
                clearConsole();
                cout << "Сотрудников нет\n";
                system("pause");
                return 1;
            }
            secretary->displayEmployeeListInTable(securityOrDriver);
            system("pause");
            return 1;
        case 5: // Управление встречами
            while (meetingManageMenu(*secretary, director))
                ;
            return 1;
        default:
            return 1;
        }
        return 1;
    }
    // функции охранника
    bool manageEmployeeMenu(SecurityGuard *securityGuard)
    {
        clearConsole();

        securityGuard->displayInfo();
        cout << endl;
        cout << "Список возможных функций:" << '\n'
             << "1. Изменить ФИО" << '\n'
             << "2. Управление спец. средством" << '\n'
             << "3. Управление статусом объектов" << '\n';

        if (!inputSingleInt(choice, 1, 3))
            return 0;

        switch (choice)
        {
        case 1: // изменение ФИО
            setFIO(*securityGuard);
            return 1;
        case 2: // Управление спец. средством
            clearConsole();
            while (manageSpecialEquipmentMenu(*securityGuard))
                ;
            return 1;
        case 3: // Управление статусом объектов
            clearConsole();
            while (manageStatusLocationsMenu(*securityGuard))
                ;
            system("pause");
            return 1;
        default:
            return 1;
        }
        return 1;
    }
    // функции водителя
    bool manageEmployeeMenu(Driver *driver)
    {
        clearConsole();

        driver->displayInfo();
        cout << endl;
        cout << "Список возможных функций:" << '\n'
             << "1. Изменить ФИО" << '\n'
             << "2. Управление водительскими правами " << '\n'
             << "3. Управление транспортом" << '\n'
             << "4. Отправить водителя в путешествие" << '\n';

        if (!inputSingleInt(choice, 1, 4))
            return 0;

        switch (choice)
        {
        case 1: // изменение ФИО
            setFIO(*driver);
            return 1;
        case 2: // Управление водительскими правами
            clearConsole();
            while (manageDriverLicenseCategoriesMenu(*driver))
                ;
            return 1;
        case 3: // Управление транспортом
            clearConsole();
            while (manageDriverVehiclesMenu(*driver))
                ;
            system("pause");
            return 1;
        case 4: // Отправить водителя в путешествие
            clearConsole();
            while (manageDriverDestinationMenu(*driver))
                ;
            system("pause");
            return 1;
        default:
            return 1;
        }
        return 1;
    }
};

char getUppercaseSymbol(int value)
{
    // Проверяем, существует ли число в массиве и возвращаем соответствующий символ
    switch (value)
    {
    // Русские символы
    case 241:
        return 'Ё';
    case 169:
        return 'Й';
    case 230:
        return 'Ц';
    case 227:
        return 'У';
    case 170:
        return 'К';
    case 165:
        return 'Е';
    case 173:
        return 'Н';
    case 163:
        return 'Г';
    case 232:
        return 'Ш';
    case 233:
        return 'Щ';
    case 167:
        return 'З';
    case 229:
        return 'Х';
    case 234:
        return 'Ъ';
    case 228:
        return 'Ф';
    case 235:
        return 'Ы';
    case 162:
        return 'В';
    case 160:
        return 'А';
    case 175:
        return 'П';
    case 224:
        return 'Р';
    case 174:
        return 'О';
    case 171:
        return 'Л';
    case 164:
        return 'Д';
    case 166:
        return 'Ж';
    case 237:
        return 'Э';
    case 239:
        return 'Я';
    case 231:
        return 'Ч';
    case 225:
        return 'С';
    case 172:
        return 'М';
    case 168:
        return 'И';
    case 226:
        return 'Т';
    case 236:
        return 'Ь';
    case 161:
        return 'Б';
    case 238:
        return 'Ю';

    // Английские символы
    case 113:
        return 'Q'; // q
    case 119:
        return 'W'; // w
    case 101:
        return 'E'; // e
    case 114:
        return 'R'; // r
    case 116:
        return 'T'; // t
    case 121:
        return 'Y'; // y
    case 117:
        return 'U'; // u
    case 105:
        return 'I'; // i
    case 111:
        return 'O'; // o
    case 112:
        return 'P'; // p
    case 97:
        return 'A'; // a
    case 115:
        return 'S'; // s
    case 100:
        return 'D'; // d
    case 102:
        return 'F'; // f
    case 103:
        return 'G'; // g
    case 104:
        return 'H'; // h
    case 106:
        return 'J'; // j
    case 107:
        return 'K'; // k
    case 108:
        return 'L'; // l
    case 122:
        return 'Z'; // z
    case 120:
        return 'X'; // x
    case 99:
        return 'C'; // c
    case 118:
        return 'V'; // v
    case 98:
        return 'B'; // b
    case 110:
        return 'N'; // n
    case 109:
        return 'M'; // m
    default:
        return '\0';
    }
}

bool Menu::inputSingleInt(int &digit, const int start, const int end) // ввод положительной цифры
{
    digit = 0;
    cout << "Введите число: ";
    char ch;
    while (true)
    {
        ch = getch();
        if (ch == 27)
            return 0;
        if (isdigit(ch))
            digit = int(ch) - 48;
        if (digit >= start && digit <= end)
            return 1;
    }
}

bool Menu::inputString(string &str, const int &minLen, const int &maxLen, bool firstBigLetter, bool allowNumbers) // ввод строки
{
    wchar_t ch;
    while (true)
    {
        ch = getch();

        // Выход при нажатии ESC
        if (int(ch) == 27) // esc
            return 0;

        // Завершение ввода при нажатии Enter, если длина строки подходит
        if (int(ch) == 13 && !str.empty() && str.length() >= minLen && str.back() != '-') // enter
            return 1;

        // Удаление последнего символа при нажатии Backspace
        if (int(ch) == 8 && !str.empty()) // del
        {
            cout << "\b \b";
            str.pop_back();
        }

        // Добавление символа, если он соответствует критериям
        if (int(ch) != 13 && int(ch) != 9 && int(ch) != 8 && str.length() < maxLen)
        {
            // Проверка на дефис: разрешен, если не первый символ и предыдущий символ не '-'
            if (ch == '-' && !str.empty() && str.back() != '-' && str.length() != maxLen - 1 && str.find('-') == string::npos)
            {
                str += char(ch);
                cout << char(ch);
            }
            // Проверка на буквы с учетом заглавной первой буквы
            else if (getUppercaseSymbol(int(ch)) != '\0')
            {
                if ((str.empty() && firstBigLetter) || (str.back() == '-' && firstBigLetter))
                {
                    str += getUppercaseSymbol(int(ch));
                    cout << getUppercaseSymbol(int(ch));
                }
                else
                {
                    str += char(ch);
                    cout << char(ch);
                }
            }
            // Проверка на цифры, если разрешен их ввод
            else if (allowNumbers && isdigit(ch))
            {
                str += char(ch);
                cout << char(ch);
            }
        }
    }
}

bool Menu::inputInt(int &number, const int &min, const int &max, const string &key, const bool minus, const bool point)
{
    string ans = "";
    char ch;
    while (true)
    {
        ch = getch();
        if (int(ch) == 27) // esc
            return 0;
        if (ch == '-' && ans.empty() && minus) // -
        {
            ans.append("-");
            cout << '-';
        }
        if (int(ch) == 13 && !ans.empty() && stoi(ans) >= min && (!ans.empty() && !(ans.length() == 1 && ans[0] == '-'))) // enter
            break;
        if (int(ch) == 9 && key == "Tab")
        {
            number = min - 1; // ЧИСЛО = -1 ЕСЛИ НАЖАЛИ TUB
            return 1;
        }
        if (int(ch) == 8 && !ans.empty()) // del
        {
            cout << "\b \b";
            ans.pop_back();
        }
        if (isdigit(ch) && stoi(ans + ch) <= max && ans.length() <= to_string(max).length())
        {
            ans += ch;
            cout << ch;
        }
    }
    if (!ans.empty())
        number = stoi(ans);
    return 1;
}

bool Menu::inputDouble(double &number, const double &min, const double &max, const string &key, const bool minus, const bool point, int decimalLimit)
{
    string ans = "";
    char ch;
    bool hasPoint = false; // Флаг для отслеживания точки
    int decimalsCount = 0; // Счётчик знаков после точки

    while (true)
    {
        ch = getch();

        if (int(ch) == 27) // ESC
            return false;

        if (ch == '-' && ans.empty() && minus) // Обработка знака "-"
        {
            ans.append("-");
            cout << '-';
        }

        // Автозаполнение "0." при вводе нуля первым символом
        if (ch == '0' && ans.empty() && point)
        {
            ans = "0.";
            hasPoint = true;
            cout << "0.";
            continue;
        }

        // Обработка ввода точки
        if (ch == '.' && point && !hasPoint && !ans.empty() && ans != "-")
        {
            ans.append(".");
            hasPoint = true;
            cout << '.';
            continue;
        }

        if (int(ch) == 13 && (!ans.empty() && !(ans.length() == 1 && ans[0] == '-'))) // ENTER
            break;

        if (int(ch) == 9 && key == "Tab") // TAB
        {
            number = min - 1; // Вернуть значение ниже минимума, если нажата Tab
            return true;
        }

        if (int(ch) == 8 && !ans.empty()) // Удаление символа (Backspace)
        {
            if (ans.back() == '.')
                hasPoint = false;
            else if (hasPoint && decimalsCount > 0)
                decimalsCount--;

            cout << "\b \b";
            ans.pop_back();
        }

        // Обработка ввода цифр с учетом диапазона min и max
        if (isdigit(ch) && (stod(ans + ch) <= max && stod(ans + ch) >= min))
        {
            // Ограничение на количество знаков после точки
            if (hasPoint && decimalsCount >= decimalLimit)
                continue;

            ans += ch;
            cout << ch;

            if (hasPoint)
                decimalsCount++;
        }
    }

    if (!ans.empty())
        number = stod(ans); // Преобразование строки в число с плавающей точкой

    return true;
}

void Menu::clearConsole() // очистка консоли и вывод сообщения "нажмите esc чтобы выйти"
{
    system("cls");
    cout << "нажмите esc чтобы выйти" << '\n'
         << '\n';
}

int main()
{
    Menu menu;
    srand(static_cast<unsigned int>(time(nullptr)));
    while (menu.createCompanyMenu())
        ;
    while (menu.CompanyMenu())
        ;
    system("cls");
    cout << "Завершения выполнения программы \n";

    system("pause");
    return 0;
}