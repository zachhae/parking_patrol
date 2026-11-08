#include "MergeSort.h"
using namespace std;

// Merge sort:
// 1. split the list in half
// 2. sort each half
// 3. merge the two sorted halves together
// Big O: O(n log n) every time

// merges tickets[left..mid] and tickets[mid+1..right]
void merge(vector<ticket>& tickets, int left, int mid, int right,
           int field1, int field2, long long& comparisons, long long& moves) {
    // copy each half into its own list
    vector<ticket> leftPart;
    vector<ticket> rightPart;
    for (int i = left; i <= mid; i++) {
        leftPart.push_back(tickets[i]);
    }
    for (int i = mid + 1; i <= right; i++) {
        rightPart.push_back(tickets[i]);
    }

    int leftSize = leftPart.size();
    int rightSize = rightPart.size();
    int i = 0;     // spot in leftPart
    int j = 0;     // spot in rightPart
    int k = left;  // spot in tickets

    // take the smaller ticket from the front of each half
    while (i < leftSize && j < rightSize) {
        comparisons++;
        // only take from the right if it is smaller.
        // if they are equal we take the left one, so the sort is stable
        if (compareTwoFields(rightPart[j], leftPart[i], field1, field2) < 0) {
            tickets[k] = rightPart[j];
            j++;
        } else {
            tickets[k] = leftPart[i];
            i++;
        }
        k++;
        moves++;
    }

    // copy whatever is left over
    while (i < leftSize) {
        tickets[k] = leftPart[i];
        i++;
        k++;
        moves++;
    }
    while (j < rightSize) {
        tickets[k] = rightPart[j];
        j++;
        k++;
        moves++;
    }
}

void mergeSortHelper(vector<ticket>& tickets, int left, int right,
                     int field1, int field2, long long& comparisons, long long& moves) {
    if (left >= right) {
        return; // 0 or 1 ticket is already sorted
    }
    int mid = (left + right) / 2;
    mergeSortHelper(tickets, left, mid, field1, field2, comparisons, moves);
    mergeSortHelper(tickets, mid + 1, right, field1, field2, comparisons, moves);
    merge(tickets, left, mid, right, field1, field2, comparisons, moves);
}

void mergeSort(vector<ticket>& tickets, int field1, int field2,
               long long& comparisons, long long& moves) {
    comparisons = 0;
    moves = 0;
    int size = tickets.size();
    mergeSortHelper(tickets, 0, size - 1, field1, field2, comparisons, moves);
}
