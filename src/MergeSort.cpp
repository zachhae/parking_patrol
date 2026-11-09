#include "MergeSort.h"
using namespace std;

static void merge(vector<ticket>& tickets, int left, int mid, int right, TicketData data, int& comparisons, int& moves) {
    vector<ticket> leftPart(tickets.begin() + left, tickets.begin() + mid + 1);
    vector<ticket> rightPart(tickets.begin() + mid + 1, tickets.begin() + right + 1);

    int i = 0;    
    int j = 0;    
    int k = left; 

    while (i < (int)leftPart.size() && j < (int)rightPart.size()) {
        comparisons++;
        if (rightPart[j].get_data_field(data) < leftPart[i].get_data_field(data)) {
            tickets[k++] = rightPart[j++];
        } else {
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

static void mergeSortHelper(vector<ticket>& tickets, int left, int right, TicketData data, int& comparisons, int& moves) {
    if (left >= right) {
        return; 
    }
    int mid = (left + right) / 2;
    mergeSortHelper(tickets, left, mid, data, comparisons, moves);
    mergeSortHelper(tickets, mid + 1, right, data, comparisons, moves);
    merge(tickets, left, mid, right, data, comparisons, moves);
}

void mergeSort(vector<ticket>& tickets, TicketData data, int& comparisons, int& moves) {
    comparisons = 0;
    moves = 0;
    mergeSortHelper(tickets, 0, (int)tickets.size() - 1, data, comparisons, moves);
}