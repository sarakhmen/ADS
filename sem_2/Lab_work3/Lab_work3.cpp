#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include "smooth_sort.h"
#include "mod_merge_sort.h"
using namespace std;


void rand_elements(vector<size_t>::iterator begin, vector<size_t>::iterator end) {
	for (; begin != end; ++begin) {
        *begin = rand() % 100000;
	}
}

void display(vector<size_t>::iterator begin, vector<size_t>::iterator end) {
	for (; begin != end; ++begin) {
        cout << *begin << ' ';
	}
	cout << endl;
}

void generate_ascending(vector<size_t>::iterator begin, vector<size_t>::iterator end, size_t start_val) {
    for (; begin != end; ++begin) {
        *begin = start_val++;
    }
}

void generate_descending(vector<size_t>::iterator begin, vector<size_t>::iterator end, size_t start_val) {
    for (; begin != end; ++begin) {
        *begin = start_val--;
    }
}


int main()
{
    vector<size_t> vec(50000);
    //rand_elements(vec.begin(), vec.end());
    //generate_descending(vec.begin(), vec.end(), 50000);
    generate_ascending(vec.begin(), vec.end(), 0);
    auto begin = chrono::high_resolution_clock::now();
    merge_sort(vec, vec.size());
    //smooth_sort(vec.begin(), vec.end());
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
    cout << "Your array: " << endl;
    //display(vec.begin(), vec.end());
    cout << "Execution time = " << duration * 1e-9 << " seconds" << endl;    
    return 0;
}
