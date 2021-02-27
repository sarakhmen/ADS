#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

using namespace std;

int main()
{
	ifstream in("word_sequence.txt", ios_base::in);
	if (!in.is_open()) {
		cout << "Error while opening file!" << endl;
		return 1;
	}

	string str;
	getline(in, str);
	cout << "Input sequence: " << str << endl;
	regex sequence_pattern("[A-Z]{1,5}(,[A-Z]{1,5}){2,29}\\.");
	if (!regex_match(str, sequence_pattern)) {
		cout << "Error: sequence doesn't match the task!" << endl;
		return 2;
	}

	map<string, size_t> result;
	regex word_pattern("[A-Z]{1,5}");
	smatch sm;

	sregex_iterator iter = sregex_iterator(str.begin(), str.end(), word_pattern);
	for (; iter != sregex_iterator(); iter++){
		sm = *iter;
		result[sm.str(0)]++;
	}

	cout << "Output: " << endl;
	for (auto& elem : result) {
		cout << elem.first << " occurs " << elem.second << " time(s);" << endl;
	}
	in.close();
	return 0;
}

