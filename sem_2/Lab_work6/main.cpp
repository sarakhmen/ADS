#include <iostream>
#include <algorithm>
#include <exception>
using namespace std;


class Stack_arr {
private:
	char* data{};
	size_t sz{1};
	size_t pos{};
public:
	Stack_arr(){
		data = new char[sz] {};
	}
	~Stack_arr() {
		if (data)
			delete[] data;
	}
	size_t size() const noexcept { return pos; }
	char pop_back() {
		if (pos > 0)
			return data[--pos];
		else
			throw underflow_error{ "Stack is empty!\n" };
	}
	void push_back(char ch) {
		if (pos < sz)
			data[pos++] = ch;
		else {
			sz *= 2;
			char* temp = new char[sz]{};
			copy(data, data + pos, temp);
			delete[] data;
			data = temp;
			data[pos++] = ch;
		}
	}
};


class Stack_list {
private:
	struct Node {
		char value{};
		Node* prev{};
	};
	Node* head{nullptr};
	size_t sz{};
public:
	Stack_list () {}
	~Stack_list() {
		Node* temp;
		while (head) {
			temp = head->prev;
			delete head;
			head = temp;
		}
	}
	size_t size() const noexcept { return sz; }
	char pop_back() {
		if (head) {
			Node* temp = head;
			char ret_val = head->value;
			head = head->prev;
			delete temp;
			--sz;
			return ret_val;
		}
		else
			throw underflow_error{ "Stack is empty!\n" };
	}
	void push_back(char ch) {
		Node* temp = new Node{ ch, nullptr };
		temp->prev = head;
		head = temp;
		++sz;
	}
};

template <typename Cust_stack>
void fill_stack(Cust_stack& st) {
	char ch{};
	cout << "Enter some chars: ";
	while ((ch = cin.get()) != '\n')
		st.push_back(ch);
}

template <typename Cust_stack>
void count(Cust_stack& st) {
	size_t a{}, o{};
	char ch;
	while (st.size()) {
		ch = st.pop_back();
		if (ch == 'a' || ch == 'A')
			++a;
		else if (ch == 'o' || ch == 'O')
			++o;
	}
	if (a == 0 && o == 0)
		cout << "There are no 'a' or 'o' characters" << endl;
	else if (a > o)
		cout << "There are more 'a' characters in the stack" << endl;
	else if (o > a)
		cout << "There are more 'o' characters in the stack" << endl;
	else
		cout << "The number of characters 'a' and 'o' is the same" << endl;
}


int main() {
	Stack_arr st_arr{};
	Stack_arr st_ls{};
	fill_stack(st_arr);
	count(st_arr);
	fill_stack(st_ls);
	count(st_ls);
	return 0;
}