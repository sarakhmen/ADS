#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <chrono>
#include <exception>
using namespace std;

template<typename T>
struct Node {
	T value{};
	Node<T>* next{};
	Node<T>* prev{};
};

template<typename T>
class my_list_iterator {
	Node<T>* ptr;
public:
	my_list_iterator(Node<T>* n) : ptr{ n } {}
	T& operator*() {
		return ptr->value;
	}
	my_list_iterator& operator++() {
		ptr = ptr->next;
		return *this;
	}
	my_list_iterator operator++(int) {
		my_list_iterator ret = *this;
		++(*this);
		return ret;
	}
	my_list_iterator& operator--() {
		ptr = ptr->prev;
		return *this;
	}
	my_list_iterator operator--(int) {
		my_list_iterator ret = *this;
		--(*this);
		return ret;
	}
};

template<typename T>
class my_list {
private:
	Node<T>* head{};
	Node<T>* tail{};
	size_t sz{};
public:
	my_list(size_t amount = 0) {
		if (amount < 0)
			throw invalid_argument{ "size of list must be greater than zero!\n" };
		for (size_t i = 0; i < amount; ++i)
			push_front(T{});
		sz = amount;
	}
	~my_list() {
		Node<T>* temp;
		while (head) {
			temp = head->next;
			delete head;
			head = temp;
		}
	}
	using iterator = my_list_iterator<T>;
	iterator begin() const noexcept { return iterator{head}; }
	iterator end() const noexcept {	return iterator{ nullptr }; }

	size_t size() const noexcept { return sz; }
	T pop_front() {
		if (head) {
			Node<T>* temp = head;
			T ret_val = head->value;
			head = head->next;
			head->prev = nullptr;
			delete temp;
			--sz;
			return ret_val;
		}
		else
			throw underflow_error{ "Stack is empty!\n" };
	}
	void push_front(T val) {
		Node<T>* temp = new Node<T>{ val, head, nullptr };
		if (!head) {
			head = tail = temp;
		}
		else {
			head->prev = temp;
			head = temp;
		}
		++sz;
	}
};

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
void reverse_every_3(my_list<T>& lst, const size_t& size) {
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
	my_list<int> lst(10000);
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

