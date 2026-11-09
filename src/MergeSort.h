#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include "ticket.h"

// Sorts the tickets using merge sort.
// comparisons and moves are counted so we can compare with quick sort.
void mergeSort(std::vector<ticket>& tickets, int field1, int field2,
               long long& comparisons, long long& moves);

#endif
