#pragma once
#include <algorithm>
#include <iterator>
#include <bitset>
#include <vector>
using namespace std;

const size_t k_num_leo_numbers = 46;

struct heap_info {
    std::bitset<k_num_leo_numbers> trees;
    size_t smallest_tree_size;
};


vector<size_t>::iterator second_child(vector<size_t>::iterator root);
vector<size_t>::iterator first_child(vector<size_t>::iterator root, size_t size);
vector<size_t>::iterator larger_child(vector<size_t>::iterator root, size_t size);
void rebalance_single_heap(vector<size_t>::iterator root, size_t size);
void leonardo_heap_rectify(vector<size_t>::iterator begin, vector<size_t>::iterator end, heap_info shape);
void leonardo_heap_add(vector<size_t>::iterator begin, vector<size_t>::iterator end, vector<size_t>::iterator heap_end,
    heap_info& shape);
void leonardo_heap_remove(vector<size_t>::iterator begin, vector<size_t>::iterator end, heap_info& shape);
void smooth_sort(vector<size_t>::iterator begin, vector<size_t>::iterator end);