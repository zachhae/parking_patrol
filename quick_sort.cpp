//
// Created by Zach Haedike on 11/7/26.
//

#include "quick_sort.h"

void quick_sort(span<ticket> sub, TicketData data) {
    if (sub.size() <= 1) {
        return;
    }

    int pivot_pointer = 0;
    int left_pointer = 1;
    int right_pointer = sub.size() - 1;

    while (left_pointer <= right_pointer) {
        while (sub[right_pointer].get_data_field(data) > sub[pivot_pointer].get_data_field(data)) {
            right_pointer--;
        }

        while (sub[left_pointer].get_data_field(data) <= sub[pivot_pointer].get_data_field(data) && left_pointer <= right_pointer) {
            left_pointer++;
        }

        if (left_pointer < right_pointer) {
            swap(sub[left_pointer], sub[right_pointer]);
        }
    }

    swap(sub[pivot_pointer], sub[right_pointer]);

    span<ticket> subarr_left(sub.begin(), right_pointer);
    span<ticket> subarr_right(sub.begin() + right_pointer + 1, sub.size() - right_pointer - 1);

    quick_sort(subarr_left, data);
    quick_sort(subarr_right, data);
}

vector<ticket> do_quick_sort(vector<ticket> arr, TicketData data) {
    span<ticket> subarr(arr.begin(), arr.size());

    quick_sort(subarr, data);

    return arr;
}