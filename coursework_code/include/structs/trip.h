#ifndef TRIP_H
#define TRIP_H

#include "date.h"

// информация о поездке
struct Trip
{
    Date dateStart;          // Дата начала поездки
    std::string destination; // Место назначения
};

#endif // TRIP_H