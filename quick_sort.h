//
// Created by Zach Haedike on 11/7/26.
//

#include <vector>
#include <span>
#include <variant>
#include "ticket.h"
using namespace std;

#ifndef PARKING_PATROL_QUICK_SORT_H
#define PARKING_PATROL_QUICK_SORT_H

/* Takes a vector of ticket structs and sorts it by 'data' using quick sort. */
vector<ticket> do_quick_sort(vector<ticket> arr, TicketData data);

#endif //PARKING_PATROL_QUICK_SORT_H
