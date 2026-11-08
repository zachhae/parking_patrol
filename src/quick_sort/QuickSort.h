#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include "../shared/Ticket.h"

// Quick sort stops if it goes over this many comparisons.
// A normal sort of 100,000 tickets uses about 2-4 million.
// The worst case (O(n^2)) would use about 5 billion.
const long long COMPARISON_LIMIT = 300000000;

// Sorts the tickets using quick sort.
// useMedian = false: the pivot is the first ticket
// useMedian = true:  the pivot is the median of first, middle, and last
// Returns true if it finished, false if it was stopped for being too slow.
bool quickSort(std::vector<Ticket>& tickets, int field1, int field2, bool useMedian,
               long long& comparisons, long long& moves);

#endif
