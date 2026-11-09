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

vector<ticket> do_quick_sort(vector<ticket> arr, TicketData data);
vector<ticket> do_quick_sort(vector<ticket> arr, TicketData data, long long& comparisons, long long& moves);

#endif //PARKING_PATROL_QUICK_SORT_H
