#include "mod_merge_sort.h"


void merge_sort(vector<size_t>& vec, size_t n)
{
    size_t curr_size;
    size_t left_start;
    for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
    {
        for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
        {
            size_t mid = min<size_t>(left_start + curr_size - 1, n - 1);
            size_t right_end = min<size_t>(left_start + 2 * curr_size - 1, n - 1);
            merge(vec, left_start, mid, right_end);
        }
    }
}

void merge(vector<size_t>& vec, size_t l, size_t m, size_t r)
{
    size_t i, j, k;
    size_t n1 = m - l + 1;
    size_t n2 = r - m;

    vector<size_t> L{ vec.begin() + l, vec.begin() + l + n1 };
    vector<size_t> R{ vec.begin() + m + 1, vec.begin() + m + 1 + n2 };
    i = 0;
    j = 0;
    k = l;
    if (i < n1 && j < n2) {
        if (L[n1 - 1] < R[0]) {
            for (; i < n1; ++i, ++k)
                vec[k] = L[i];
        }

        else if (L[0] > R[n2 - 1]) {
            for (; j < n2; ++j, ++k)
                vec[k] = R[j];
        }

        else
            do {
                if (L[i] <= R[j]) {
                    vec[k] = L[i];
                    i++;
                }
                else {
                    vec[k] = R[j];
                    j++;
                }
                k++;
            } while (i < n1 && j < n2);
    }
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}