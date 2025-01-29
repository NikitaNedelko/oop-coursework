#include "utils/enum_to_string.h"

namespace app
{

    std::string toStringEnum(Position position)
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

    std::string toStringEnum(Department department)
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

    std::string toStringEnum(Equipment equipment)
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

    std::string toStringEnum(VehicleType vehicle)
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

    std::string toStringEnum(DriverLicense license)
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

} // namespace app