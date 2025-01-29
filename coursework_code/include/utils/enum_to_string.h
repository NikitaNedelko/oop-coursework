#ifndef ENUM_TO_STRING_H
#define ENUM_TO_STRING_H

#include <string>
#include "enums/position.h"
#include "enums/department.h"
#include "enums/equipment.h"
#include "enums/vehicle_type.h"
#include "enums/driver_license.h"

namespace app
{

    // функция для получения строкового представления должности
    std::string toStringEnum(Position position);
    // функция для получения строкового представления отдела
    std::string toStringEnum(Department department);
    // функция для получения строкового представления спецсредства
    std::string toStringEnum(Equipment equipment);
    // функция для получения строкового представления типа транспорта
    std::string toStringEnum(VehicleType vehicle);
    // функция для получения строкового представления водительских прав
    std::string toStringEnum(DriverLicense license);

} // namespace app

#endif // ENUM_TO_STRING_H