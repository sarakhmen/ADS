#include "smooth_sort.h"


const size_t k_leo_numbers[k_num_leo_numbers] = {
    1u, 1u, 3u, 5u, 9u, 15u, 25u, 41u, 67u, 109u, 177u, 287u, 465u, 753u,
    1219u, 1973u, 3193u, 5167u, 8361u, 13529u, 21891u, 35421u, 57313u, 92735u,
    150049u, 242785u, 392835u, 635621u, 1028457u, 1664079u, 2692537u,
    4356617u, 7049155u, 11405773u, 18454929u, 29860703u, 48315633u, 78176337u,
    126491971u, 204668309u, 331160281u, 535828591u, 866988873u, 1402817465u,
    2269806339u, 3672623805u
};


vector<size_t>::iterator second_child(vector<size_t>::iterator root) {
    return root - 1;
}

vector<size_t>::iterator first_child(vector<size_t>::iterator root, size_t size) {
    return second_child(root) - k_leo_numbers[size - 2];
}


vector<size_t>::iterator larger_child(vector<size_t>::iterator root, size_t size) {
    vector<size_t>::iterator first = first_child(root, size);
    vector<size_t>::iterator second = second_child(root);
    return less<size_t>()(*first, *second) ? second : first;
}

void rebalance_single_heap(vector<size_t>::iterator root, size_t size) {
    while (size > 1) {
        vector<size_t>::iterator first = first_child(root, size);
        vector<size_t>::iterator second = second_child(root);
        vector<size_t>::iterator larger_child;
        size_t child_size;
        if (less<size_t>()(*first, *second)) {
            larger_child = second;
            child_size = size - 2;
        }
        else {
            larger_child = first;
            child_size = size - 1;
        }
        if (!less<size_t>()(*root, *larger_child))
            return;
        std::iter_swap(root, larger_child);
        root = larger_child;
        size = child_size;
    }
}


void leonardo_heap_rectify(vector<size_t>::iterator begin, vector<size_t>::iterator end, heap_info shape) {
    vector<size_t>::iterator itr = end - 1;
    size_t lastHeapSize;
    while (true) {
        lastHeapSize = shape.smallest_tree_size;
        if (size_t(std::distance(begin, itr)) == k_leo_numbers[lastHeapSize] - 1)
            break;
        vector<size_t>::iterator to_compare = itr;
        if (shape.smallest_tree_size > 1) {
            vector<size_t>::iterator large_child = larger_child(itr, shape.smallest_tree_size);
            if (less<size_t>()(*to_compare, *large_child))
                to_compare = large_child;
        }
        vector<size_t>::iterator prior_heap = itr - k_leo_numbers[lastHeapSize];
        if (!less<size_t>()(*to_compare, *prior_heap))
            break;
        std::iter_swap(itr, prior_heap);
        itr = prior_heap;
        do {
            shape.trees >>= 1;
            ++shape.smallest_tree_size;
        } while (!shape.trees[0]);
    }

    rebalance_single_heap(itr, lastHeapSize);
}

void leonardo_heap_add(vector<size_t>::iterator begin, vector<size_t>::iterator end,
    vector<size_t>::iterator heap_end,
    heap_info& shape) {
    if (!shape.trees[0]) {
        shape.trees[0] = true;
        shape.smallest_tree_size = 1;
    }
    else if (shape.trees[1] && shape.trees[0]) {
        shape.trees >>= 2;
        shape.trees[0] = true;
        shape.smallest_tree_size += 2;
    }
    else if (shape.smallest_tree_size == 1) {
        shape.trees <<= 1;
        shape.smallest_tree_size = 0;
        shape.trees[0] = true;
    }
    else {
        shape.trees <<= shape.smallest_tree_size - 1;
        shape.trees[0] = true;
        shape.smallest_tree_size = 1;
    }
    bool isLast = false;
    switch (shape.smallest_tree_size) {
    case 0:
        if (end + 1 == heap_end)
            isLast = true;
        break;

    case 1:
        if (end + 1 == heap_end || (end + 2 == heap_end && !shape.trees[1]))
            isLast = true;
        break;

    default:
        if (size_t(std::distance(end + 1, heap_end)) < k_leo_numbers[shape.smallest_tree_size - 1] + 1)
            isLast = true;
        break;
    }

    if (!isLast)
        rebalance_single_heap(end, shape.smallest_tree_size);
    else
        leonardo_heap_rectify(begin, end + 1, shape);
}


void leonardo_heap_remove(vector<size_t>::iterator begin, vector<size_t>::iterator end,
    heap_info& shape) {

    if (shape.smallest_tree_size <= 1) {

        do {
            shape.trees >>= 1;
            ++shape.smallest_tree_size;
        } while (shape.trees.any() && !shape.trees[0]);
        return;
    }
    const size_t heap_order = shape.smallest_tree_size;
    shape.trees[0] = false;
    shape.trees <<= 2;
    shape.trees[1] = shape.trees[0] = true;
    shape.smallest_tree_size -= 2;
    vector<size_t>::iterator left_heap = first_child(end - 1, heap_order);
    vector<size_t>::iterator right_heap = second_child(end - 1);
    heap_info allButLast = shape;
    ++allButLast.smallest_tree_size;
    allButLast.trees >>= 1;
    leonardo_heap_rectify(begin, left_heap + 1, allButLast);
    leonardo_heap_rectify(begin, right_heap + 1, shape);
}



void smooth_sort(vector<size_t>::iterator begin, vector<size_t>::iterator end) {
    if (begin == end || begin + 1 == end) return;
    heap_info shape;
    shape.smallest_tree_size = 0;
    for (vector<size_t>::iterator itr = begin; itr != end; ++itr)
        leonardo_heap_add(begin, itr, end, shape);

    for (vector<size_t>::iterator itr = end; itr != begin; --itr)
        leonardo_heap_remove(begin, itr, shape);
}