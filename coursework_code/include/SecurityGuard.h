#ifndef SECURITY_GUARD_H
#define SECURITY_GUARD_H

#include <map>
#include <vector>
#include <string>
#include "structs/personal_data.h"
#include "enums/equipment.h"
#include "utils/enum_to_string.h"
#include "Person.h"

// класс SecurityGuard, наследуемый от Person
class SecurityGuard : public Person
{
private:
    PersonalData personalData;
    // Место -> Статус проверки
    std::map<std::string, std::string> locations;
    // Название спецсредства (дубинка, шокер и т.д.)
    Equipment specialEquipment;
    // Список всех объектов
    std::vector<std::string> departments = {"Склад", "Производство", "Администрация", "Лаборатория"};
    // Список возможных статусов
    std::vector<std::string> statuses = {"Всё в порядке", "Нужна проверка", "Нарушение безопасности",
                                         "Неизвестный статус"};

public:
    SecurityGuard(const PersonalData &personalData, const Equipment &equipment);

    // Геттеры и сеттеры для полей Human
    void setFirstName(const std::string &firstName) override;
    std::string getFirstName() const override;
    void setLastName(const std::string &lastName) override;
    std::string getLastName() const override;
    void setMiddleName(const std::string &middleName) override;
    std::string getMiddleName() const override;
    void setSalary(double salary) override;
    double getSalary() const override;

    // Метод для изменения статуса безопасности
    void setSecurityStatus(std::string &department, std::string &status);
    // Метод для генерации отчета о безопасности
    void generateIncidentReport() const;
    void setSpecialEquipment(const Equipment equipment);
    Equipment getSpecialEquipment() const;
    // все объекты
    std::vector<std::string> allDepartments();
    // все статусы
    std::vector<std::string> allStatuses();
    // вся информация о классе
    void displayInfo() const;
};

#endif // SECURITY_GUARD_H