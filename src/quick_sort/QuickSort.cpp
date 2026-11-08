#include "QuickSort.h"
using namespace std;

// Quick sort:
// 1. pick a pivot
// 2. move smaller tickets to the left and bigger tickets to the right
// 3. sort the left side and the right side
// Big O: O(n log n) on average, O(n^2) in the worst case
// (worst case = first pivot on data that is already sorted)

// swaps two tickets and counts it (a swap = 3 moves)
void swapTickets(vector<Ticket>& tickets, int a, int b, long long& moves) {
    Ticket temp = tickets[a];
    tickets[a] = tickets[b];
    tickets[b] = temp;
    moves = moves + 3;
}

// puts first, middle, last in order, then moves the middle one
// (the median) to the front so it becomes the pivot
void medianOfThree(vector<Ticket>& tickets, int low, int high,
                   int field1, int field2, long long& comparisons, long long& moves) {
    int mid = (low + high) / 2;

    comparisons++;
    if (compareTwoFields(tickets[mid], tickets[low], field1, field2) < 0) {
        swapTickets(tickets, mid, low, moves);
    }
    comparisons++;
    if (compareTwoFields(tickets[high], tickets[low], field1, field2) < 0) {
        swapTickets(tickets, high, low, moves);
    }
    comparisons++;
    if (compareTwoFields(tickets[high], tickets[mid], field1, field2) < 0) {
        swapTickets(tickets, high, mid, moves);
    }

    swapTickets(tickets, low, mid, moves);
}

// Hoare partition. The pivot is tickets[low].
// i moves right until it finds a ticket >= pivot.
// j moves left until it finds a ticket <= pivot.
// Then we swap them. Stopping on equal tickets keeps the sides even
// when there are lots of the same value (like all the $0 fines).
int partition(vector<Ticket>& tickets, int low, int high,
              int field1, int field2, long long& comparisons, long long& moves) {
    Ticket pivot = tickets[low];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
            comparisons++;
        } while (compareTwoFields(tickets[i], pivot, field1, field2) < 0);

        do {
            j--;
            comparisons++;
        } while (compareTwoFields(tickets[j], pivot, field1, field2) > 0);

        if (i >= j) {
            return j;
        }
        swapTickets(tickets, i, j, moves);
    }
}

void quickSortHelper(vector<Ticket>& tickets, int low, int high, int field1, int field2,
                     bool useMedian, long long& comparisons, long long& moves, bool& stopped) {
    while (low < high) {
        if (comparisons > COMPARISON_LIMIT) {
            stopped = true;
            return;
        }

        if (useMedian) {
            medianOfThree(tickets, low, high, field1, field2, comparisons, moves);
        }
        int p = partition(tickets, low, high, field1, field2, comparisons, moves);

        // Sort the smaller side with recursion, then loop again for the bigger side.
        // If we used recursion on both sides, sorted data would make
        // 100,000 calls in a row and the program could crash.
        if (p - low < high - p) {
            quickSortHelper(tickets, low, p, field1, field2, useMedian, comparisons, moves, stopped);
            low = p + 1;
        } else {
            quickSortHelper(tickets, p + 1, high, field1, field2, useMedian, comparisons, moves, stopped);
            high = p;
        }
    }
}

bool quickSort(vector<Ticket>& tickets, int field1, int field2, bool useMedian,
               long long& comparisons, long long& moves) {
    comparisons = 0;
    moves = 0;
    bool stopped = false;
    int size = tickets.size();
    quickSortHelper(tickets, 0, size - 1, field1, field2, useMedian, comparisons, moves, stopped);
    return !stopped;
}
