//
// Created by Zach Haedike on 11/7/26.
//

#include "quick_sort.h"

vector<int> do_quick_sort(vector<int> arr) {
    span<int> subarr(arr.begin(), arr.size());

    quick_sort(subarr);

    return arr;
}

void quick_sort(span<int> sub) {
    if (sub.size() <= 1) {
        return;
    }

    int pivot_pointer = 0;
    int left_pointer = 1;
    int right_pointer = sub.size() - 1;

    while (left_pointer <= right_pointer) {
        while (sub[right_pointer] > sub[pivot_pointer]) {
            right_pointer--;
        }

        while (sub[left_pointer] <= sub[pivot_pointer] && left_pointer <= right_pointer) {
            left_pointer++;
        }

        if (left_pointer < right_pointer) {
            swap(sub[left_pointer], sub[right_pointer]);
        }
    }

    swap(sub[pivot_pointer], sub[right_pointer]);

    span<int> subarr_left(sub.begin(), right_pointer);
    span<int> subarr_right(sub.begin() + right_pointer + 1, sub.size() - right_pointer - 1);

    quick_sort(subarr_left);
    quick_sort(subarr_right);
}