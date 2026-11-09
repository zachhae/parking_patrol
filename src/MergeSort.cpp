#include "MergeSort.h"
using namespace std;

void merge(vector<ticket>& tickets, int left, int mid, int right, int field1, int field2, int& comparisons, int& moves) {
    vector<ticket> leftPart(tickets.begin() + left, tickets.begin() + mid + 1);
    vector<ticket> rightPart(tickets.begin() + mid + 1, tickets.begin() + right + 1);
    
    int i = 0;    
    int j = 0;     
    int k = left;  

    while (i < (int)leftPart.size() && j < (int)rightPart.size()) {
        comparisons++;
        if (compareTwoFields(rightPart[j], leftPart[i], field1, field2) < 0) {
            tickets[k++] = rightPart[j++];
        } 
        else {
            tickets[k++] = leftPart[i++];
        }
        moves++;
    }

    while (i < (int)leftPart.size()) {
        tickets[k++] = leftPart[i++];
        moves++;
    }
    while (j < (int)rightPart.size()) {
        tickets[k++] = rightPart[j++];
        moves++;
    }
}

void mergeSortHelper(vector<ticket>& tickets, int left, int right, int field1, int field2, int& comparisons, int& moves) {
    if (left >= right) {
        return; 
    }
    int mid = (left + right) / 2;
    mergeSortHelper(tickets, left, mid, field1, field2, comparisons, moves);
    mergeSortHelper(tickets, mid + 1, right, field1, field2, comparisons, moves);
    merge(tickets, left, mid, right, field1, field2, comparisons, moves);
}

void mergeSort(vector<ticket>& tickets, int field1, int field2, int& comparisons, int& moves) {
    comparisons = 0;
    moves = 0;
    mergeSortHelper(tickets, 0, (int)tickets.size() - 1, field1, field2, comparisons, moves);
}
