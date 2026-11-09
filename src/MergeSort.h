#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include "ticket.h"

const int NONE = 0;
const int PLATE = 1;
const int STREET = 2;
const int VIOLATION = 3;
const int FINE = 4;
const int DATE = 5;

void mergeSort(std::vector<ticket>& tickets, int field1, int field2, int& comparisons, int& moves);

#endif
