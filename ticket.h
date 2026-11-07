//
// Created by Zach Haedike on 11/7/26.
//

#include <string>
using namespace std;

#ifndef PARKING_PATROL_TICKET_H
#define PARKING_PATROL_TICKET_H


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
};


#endif //PARKING_PATROL_TICKET_H
