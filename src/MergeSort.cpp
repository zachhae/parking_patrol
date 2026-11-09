#include "MergeSort.h"
using namespace std;

//Compare functions to help sort data
static int compareValues(double a, double b) {
    if (a < b) 
        return -1;
    if (a > b) 
        return 1;
    return 0;
}

static int compareStrings(const string& a, const string& b) {
    if (a < b) 
        return -1;
    if (a > b) 
        return 1;
    return 0;
}

static int compareOneField(const ticket& a, const ticket& b, int field) {
    if (field == PLATE)     
        return compareStrings(a.plate_number, b.plate_number);
    if (field == STREET)    
        return compareStrings(a.location, b.location);
    if (field == VIOLATION) 
        return compareStrings(a.violation, b.violation);
    if (field == FINE)      
        return compareValues(a.fine, b.fine);
    if (field == DATE) {
        if (a.year != b.year)   
            return compareValues(a.year, b.year);
        if (a.month != b.month) 
            return compareValues(a.month, b.month);
        if (a.day != b.day)     
            return compareValues(a.day, b.day);
        if (a.hour != b.hour)   
            return compareValues(a.hour, b.hour);
        return compareValues(a.minute, b.minute);
    }
    return 0;
}

static int compareTwoFields(const ticket& a, const ticket& b, int field1, int field2) {
    int result = compareOneField(a, b, field1);
    if (result == 0 && field2 != NONE) {
        result = compareOneField(a, b, field2);
    }
    return result;
}

//Merge sort
static void merge(vector<ticket>& tickets, int left, int mid, int right, int field1, int field2, int& comparisons, int& moves) {
    vector<ticket> leftPart(tickets.begin() + left, tickets.begin() + mid + 1);
    vector<ticket> rightPart(tickets.begin() + mid + 1, tickets.begin() + right + 1);

    int i = 0;    
    int j = 0;   
    int k = left;  

    while (i < (int)leftPart.size() && j < (int)rightPart.size()) {
        comparisons++;
        if (compareTwoFields(rightPart[j], leftPart[i], field1, field2) < 0) {
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

static void mergeSortHelper(vector<ticket>& tickets, int left, int right, int field1, int field2, int& comparisons, int& moves) {
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
