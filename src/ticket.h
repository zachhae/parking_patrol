//
// Created by Zach Haedike on 11/7/26.
//

#include <string>
#include <variant>
using namespace std;

#ifndef PARKING_PATROL_TICKET_H
#define PARKING_PATROL_TICKET_H

enum class TicketData {
    Plate_Number, State, Vehicle_Make, Vehicle_Style, Vehicle_Color, Location, Violation,
    Fine, Year, Month, Day, Hour, Minute, Date
};

struct ticket {
    string plate_number;
    string state;
    string vehicle_make;
    string vehicle_style;
    string vehicle_color;
    string location;
    string violation;
    double fine;
    int year;
    int month;
    int day;
    int hour;
    int minute;

    /* Returns the data in the struct member specified by TicketData */
    variant<string, int, double> get_data_field(TicketData data) const {
        switch (data) {
            case TicketData::Plate_Number: return plate_number;
            case TicketData::State: return state;
            case TicketData::Vehicle_Make: return vehicle_make;
            case TicketData::Vehicle_Style: return vehicle_style;
            case TicketData::Vehicle_Color: return vehicle_color;
            case TicketData::Location: return location;
            case TicketData::Violation: return violation;
            case TicketData::Fine: return fine;
            case TicketData::Year: return year;
            case TicketData::Month: return month;
            case TicketData::Day: return day;
            case TicketData::Hour: return hour;
            case TicketData::Minute: return minute;
            case TicketData::Date:
                return year * 100000000.0 + month * 1000000.0 + day * 10000.0 + hour * 100.0 + minute;
        }
    }
};


#endif //PARKING_PATROL_TICKET_H
