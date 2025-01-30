#ifndef DRIVER_H
#define DRIVER_H

#include <vector>
#include <string>
#include "structs/personal_data.h"
#include "enums/driver_license.h"
#include "enums/vehicle_type.h"
#include "Person.h"

// класс Driver, наследуемый от Person
class Driver : public Person
{
private:
    PersonalData personalData;

    std::string destination;
    // Массив категорий прав (например, A, B, C)
    std::vector<DriverLicense> licenseCategories;
    // Массив транспортных средств, которыми управляет водитель
    std::vector<VehicleType> vehicles;
    std::vector<std::string> cities;

public:
    Driver(const PersonalData &personalData, DriverLicense licenseCategories,
           VehicleType vehicles);

    // Геттеры и сеттеры для полей Human
    void setFirstName(const std::string &firstName) override;
    std::string getFirstName() const override;
    void setLastName(const std::string &lastName) override;
    std::string getLastName() const override;
    void setMiddleName(const std::string &middleName) override;
    std::string getMiddleName() const override;
    void setSalary(double salary) override;
    double getSalary() const override;

    // новое место назначение
    void changeDestination(const std::string &newDestination);
    // список городов (доступных мест назначений)
    const std::vector<std::string> getCities();
    // Метод для добавления категории водительских прав
    void addLicenseCategory(const DriverLicense &category);
    // Метод для получения категории водительских прав
    std::vector<DriverLicense> &getLicenseCategories();
    // Метод для добавления транспортного средства
    void addVehicle(const VehicleType &vehicle);
    // Метод вывода всех транспортных средств
    std::vector<VehicleType> &getVehicles();
    // отображение всей информации класса
    void displayInfo() const;
};

#endif // DRIVER_H