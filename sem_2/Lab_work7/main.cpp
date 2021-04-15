#include <iostream>
#include <string>
using namespace std;

struct Node {
	string name;
	int value;
	Node* left;
	Node* right;
};

class Tree {
	Node* root;
	void delete_node(Node* leaf) {
		if (leaf) {
			delete_node(leaf->left);
			delete_node(leaf->right);
			delete leaf;
		}
	}
	void inorder_print(Node* leaf) {
		if (leaf) {
			inorder_print(leaf->left);
			cout << "<" << leaf->name << ", " << leaf->value << ">   ";
			inorder_print(leaf->right);
		}
	}
	void change_val(Node* leaf, int new_val) {
		if (leaf) {
			leaf->value = new_val;
			change_val(leaf->left, new_val);
			change_val(leaf->right, new_val);
		}
	}

public:
	Tree() : root{nullptr} {}
	~Tree() {
		delete_node(root);
	}
	void insert(string name, int value) {
		Node* temp = new Node{ name, value, nullptr, nullptr };
		if (!root)
			root = temp;
		else{
			Node* curr = root;
			while (true) {
				if (name < curr->name) {
					if (!curr->left) {
						curr->left = temp;
						return;
					}
					curr = curr->left;
				}
				else {
					if (!curr->right) {
						curr->right = temp;
						return;
					}
					curr = curr->right;
				}
			}
		}
	}
	void inorder_print() {
		if (root){
			inorder_print(root->left);
			cout << "<(root)" << root->name << ", " << root->value << ">   ";
			inorder_print(root->right);
		}
	}
	void change_val_left_sbtr(int new_val) {
		if (root)
			change_val(root->left, new_val);
	}
};


int main() {
	Tree tr;
	tr.insert("L", 10);
	tr.insert("B", 12);
	tr.insert("D", 14);
	tr.insert("A", 5);
	tr.insert("K", 55);
	tr.insert("X", 125);
	tr.insert("M", 4);
	tr.insert("E", -1);
	cout << "Tree content before:" << endl;
	tr.inorder_print();
	tr.change_val_left_sbtr(100);
	cout << "\n\nTree content after:" << endl;;
	tr.inorder_print();
	return 0;
}