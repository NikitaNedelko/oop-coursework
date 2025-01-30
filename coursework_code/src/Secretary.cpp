#include "Secretary.h"

using namespace std;
using namespace app;

Secretary::Secretary(const PersonalData &personalData)
{
    setFirstName(personalData.firstName);
    setMiddleName(personalData.middleName);
    setLastName(personalData.lastName);
}

// Геттеры и сеттеры для полей Human
void Secretary::setFirstName(const std::string &firstName) { personalData.firstName = firstName; }

std::string Secretary::getFirstName() const { return personalData.firstName; }

void Secretary::setLastName(const std::string &lastName) { personalData.lastName = lastName; }

std::string Secretary::getLastName() const { return personalData.lastName; }

void Secretary::setMiddleName(const std::string &middleName) { personalData.middleName = middleName; }

std::string Secretary::getMiddleName() const { return personalData.middleName; }

void Secretary::setSalary(double salary) { personalData.salary = salary; }

double Secretary::getSalary() const { return personalData.salary; }

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
                cout << left << setw(2) << employeeNumber++ << setw(10) << "|" + positionName
                     << setw(16) << "|" + employee->getMiddleName() << setw(16)
                     << "|" + employee->getFirstName() << setw(16) << "|" + employee->getLastName()
                     << "|" << setw(9) << fixed << setprecision(2) << employee->getSalary()
                     << " руб.|" << endl;
                cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
                     << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+'
                     << endl;
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
                if (find(meeting.employees.begin(), meeting.employees.end(), employee) !=
                    meeting.employees.end())
                {
                    system("cls");
                    cout << "Сотрудник " << employee->getMiddleName() << " "
                         << employee->getFirstName() << " уже занят на встрече в это время.\n";
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

vector<Meeting> &Secretary::listScheduledMeetings() { return meetings; }

void Secretary::displayMeetings() const
{
    cout << "Запланированные встречи:\n\n";
    int index = 0;
    for (const auto &meeting : meetings)
    {
        cout << ++index << ") Место: " << meeting.place << ", Дата: " << meeting.date.toStringDate()
             << "\n";
    }
}

void Secretary::participantsOfMeeting(Meeting meeting) const
{
    cout << "Место: " << meeting.place << ", Дата: " << meeting.date.toStringDate() << "\n";
    cout << "Сотрудники: \n";
    for (const auto &emp : meeting.employees)
    {
        cout << emp->getMiddleName() << " " << emp->getFirstName() << " " << emp->getLastName()
             << endl;
    }
    cout << "\n";
}

void Secretary::displayInfo() const
{
    cout << left << setw(3) << "№ |" << setw(10) << "Должность|" << setw(45)
         << "    Фамилия    |      Имя      |   Отчество    |"
         << "   Зарплата   |" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
         << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;

    cout << left << setw(2) << 0 << setw(10) << "|" + toStringEnum(Position::Secretary) << setw(16)
         << "|" + getMiddleName() << setw(16) << "|" + getFirstName() << setw(16)
         << "|" + getLastName() << "|" << setw(9) << fixed << setprecision(2) << getSalary()
         << " руб.|" << endl;
    cout << string(2, '-') << '+' << string(9, '-') << '+' << string(15, '-') << '+'
         << string(15, '-') << '+' << string(15, '-') << '+' << string(14, '-') << '+' << endl;
}
