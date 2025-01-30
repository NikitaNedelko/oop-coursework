#ifndef TRIP_H
#define TRIP_H

#include "classes/Date.h"

// информация о поездке
struct Trip
{
    Date dateStart;          // Дата начала поездки
    std::string destination; // Место назначения
};

#endif // TRIP_H