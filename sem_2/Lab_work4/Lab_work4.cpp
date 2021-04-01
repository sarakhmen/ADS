#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
using namespace std;

const string chars = "tyuiopasdfghjcvbnm";

void erase_iter(string& txt, string& excl);
string erase_rec(string& txt, string& excl, int beg_pos);
string gen_word();
string gen_text(int len);
long long evaluate_iter(string& txt, string& excl);
long long evaluate_rec(string& txt, string& excl);



int main() {
	ofstream fout("results.txt");
	string txt1,
		   txt2,
		   excl = "no";	
	txt1 = txt2 = gen_text(100);
	fout << "iterative version for 100 symbols:\n\texecution time = " << evaluate_iter(txt1, excl) * 1e-9 << " seconds" << endl;
	fout << "recursive version for 100 symbols:\n\texecution time = " << evaluate_rec(txt2, excl) * 1e-9 << " seconds" << endl;
	fout << endl;
	txt1 = txt2 = gen_text(5000);
	fout << "iterative version for 5000 symbols:\n\texecution time = " << evaluate_iter(txt1, excl) * 1e-9 << " seconds" << endl;
	fout << "recursive version for 5000 symbols:\n\texecution time = " << evaluate_rec(txt2, excl) * 1e-9 << " seconds" << endl;
	fout << endl;
	txt1 = txt2 = gen_text(9000);
	fout << "iterative version for 8220 symbols:\n\texecution time = " << evaluate_iter(txt1, excl) * 1e-9 << " seconds" << endl;
	fout << "recursive version for 8220 symbols:\n\texecution time = " << evaluate_rec(txt2, excl) * 1e-9 << " seconds" << endl;
	fout << endl;
	fout.close();
	return 0;
}


void erase_iter(string& txt, string& excl) {
	string temp;
	stringstream ss(txt);
	txt.clear();
	while (ss >> temp) {
		if (temp != excl)
			txt += temp + ' ';
	}
}


string erase_rec(string& txt, string& excl, int beg_pos) {
	string temp;
	int end_pos;

	end_pos = txt.find_first_of(' ', beg_pos);

	if (end_pos == string::npos) {
		temp = txt.substr(beg_pos);
		if (temp == excl)
			return "";
		else
			return temp;
	}
	else {
		temp = txt.substr(beg_pos, end_pos - beg_pos);
		if (temp == excl)
			return erase_rec(txt, excl, end_pos + 1);
		else
			return temp + ' ' + erase_rec(txt, excl, end_pos + 1);
	}
}


string gen_word() {
	string word;
	int len = rand() % 5 + 1;
	int i;
	for (i = 0; i < len; ++i)
		word.push_back(chars[rand() % (chars.size())]);
	word.push_back(' ');
	return word;
}


string gen_text(int len) {
	string txt;
	int counter = 0;
	while (txt.size() < len) {
		++counter;
		if (counter % 4 == 0)
			txt += "no ";
		else
			txt += gen_word();
	}
	while ((txt.size() - len) > 0) {
		txt.pop_back();
	}
	return txt;
}


long long evaluate_iter(string& txt, string& excl) {
	auto begin = chrono::high_resolution_clock::now();
	erase_iter(txt, excl);
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
}


long long evaluate_rec(string& txt, string& excl) {
	auto begin = chrono::high_resolution_clock::now();
	erase_rec(txt, excl, 0);
	auto end = chrono::high_resolution_clock::now();
	return chrono::duration_cast<chrono::nanoseconds>(end - begin).count();
}







//void erase_iter(char *text, int &txt_sz, char *to_exclude, int &excl_sz) {
//	for (int i = 0; i < txt_sz - excl_sz + 1; ++i) {
//		for (int j = 0; j < excl_sz; ++j) {
//			if (text[i + j] != to_exclude[j]) {
//				break;
//			}
//			else {
//				if (j == excl_sz - 1) {
//					if ((((i - 1) == -1) || isspace(text[i - 1])) && (((i + excl_sz) == txt_sz) || isspace(text[i + excl_sz]))) {
//						for (int k = 0; k < excl_sz; ++k) {
//							for (int z = i; z < txt_sz; ++z) {
//								text[z] = text[z + 1];
//							}
//							--txt_sz;
//						}
//					}
//				}
//			}
//		}
//
//	}
//}

