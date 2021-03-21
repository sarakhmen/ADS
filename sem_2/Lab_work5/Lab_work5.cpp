#include <iostream>
#include <fstream>
#include <list>
#include <array>
#include <algorithm>
#include <chrono>
using namespace std;

template <class Container>
void fill_with_num(Container& container, const size_t &amount) {
	auto iter = container.begin();
	for (size_t i = 0; i < amount; ++i, ++iter) {
		*iter = i;
	}
}

template <class Container>
void print(const Container& container, const size_t &size, const char *tag) {
	cout << tag << endl;
	auto iter = container.begin();
	for (size_t i = 0; i < size; ++i, ++iter)
		cout << *iter << ' ';
	cout << endl;
}

template <class T>
void reverse_every_3(list<T>& lst, const size_t& size) {
	auto iter = lst.begin();
	auto temp = iter;
	for (size_t i = 2; i < size; i+=3, ++iter, temp = iter) {
		++++iter,
		iter_swap(temp, iter);
	}
}

template <class T>
void reverse_every_3(array<T, 10000> &arr, const size_t& size) {
	for (int i = 2; i < size; i += 3)
		swap(arr[i], arr[i - 2]);
}

template <class Container>
long long evaluate(Container& container, const size_t& size) {
	fill_with_num(container, size);
	auto begin = chrono::high_resolution_clock::now();
	reverse_every_3(container, size);
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
}

int main()
{
	ofstream fout("results.txt");
	list<int> lst(10000);
	auto *arr = new array<int, 10000>;

	fout << "Reverse every three elements of the LIST of 10 element:\n\tExecution time = " << evaluate(lst, 10) * 1e-9 << " seconds" << endl;
	fout << "Reverse every three elements of the ARRAY of 10 element:\n\tExecution time = " << evaluate(*arr, 10) * 1e-9 << " seconds" << endl;
	fout << endl;
	print(lst, 10, "list contents: ");
	print(*arr, 10, "array contents: ");

	fout << "Reverse every three elements of the LIST of 10000 element:\n\tExecution time = " << evaluate(lst, 10000) * 1e-9 << " seconds" << endl;
	fout << "Reverse every three elements of the ARRAY of 10000 element:\n\tExecution time = " << evaluate(*arr, 10000) * 1e-9 << " seconds" << endl;
	fout << endl;
	print(lst, 10000, "list contents: ");
	print(*arr, 10000, "array contents: ");

	fout.close();
	return 0;
}

