//
// Created by Zach Haedike on 11/7/26.
//

#include "quick_sort.h"
#include <span>

/* Sorts 'sub' using the first item as the pivot. */
static void quick_sort(span<ticket> sub, TicketData data, long long& comparisons, long long& moves) {
    // Loop instead of recursing on the bigger side. With a first-item pivot,
    // sorted data makes one side empty every time; recursing on that side
    // 100,000 times would crash the program (stack overflow).
    while (sub.size() > 1) {
        int pivot_pointer = 0;
        int left_pointer = 1;
        int right_pointer = sub.size() - 1;
        auto pivot = sub[pivot_pointer].get_data_field(data);

        while (left_pointer <= right_pointer) {
            // move right_pointer left past items bigger than the pivot
            while (comparisons++, sub[right_pointer].get_data_field(data) > pivot) {
                right_pointer--;
            }

            // move left_pointer right past items smaller or equal to the pivot
            // (check the bounds FIRST, so we never read past the end)
            while (left_pointer <= right_pointer &&
                   (comparisons++, sub[left_pointer].get_data_field(data) <= pivot)) {
                left_pointer++;
            }

            if (left_pointer < right_pointer) {
                swap(sub[left_pointer], sub[right_pointer]);
                moves++;
            }
        }

        // put the pivot in its final spot
        swap(sub[pivot_pointer], sub[right_pointer]);
        moves++;

        span<ticket> subarr_left = sub.subspan(0, right_pointer);
        span<ticket> subarr_right = sub.subspan(right_pointer + 1);

        // recurse on the smaller side, loop on the bigger side
        if (subarr_left.size() < subarr_right.size()) {
            quick_sort(subarr_left, data, comparisons, moves);
            sub = subarr_right;
        } else {
            quick_sort(subarr_right, data, comparisons, moves);
            sub = subarr_left;
        }
    }
}

vector<ticket> do_quick_sort(vector<ticket> arr, TicketData data,
                             long long& comparisons, long long& moves) {
    comparisons = 0;
    moves = 0;
    quick_sort(span<ticket>(arr), data, comparisons, moves);
    return arr;
}

vector<ticket> do_quick_sort(vector<ticket> arr, TicketData data) {
    long long comparisons, moves;
    return do_quick_sort(arr, data, comparisons, moves);
}