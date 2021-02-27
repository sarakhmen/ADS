#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <map>

using namespace std;

void modify_str(string&, map<char, unsigned>&);

int main()
{
    string str;
    map<char, unsigned> mp;
    cout << "Enter your string (3 or more words): ";
    getline(cin, str);
    modify_str(str, mp);
    if (str == "") {
        cout << "Error: you've entered less than 3 words" << endl;
        return 1;
    }
    cout << "Output: " << str << endl;
    cout << "\n*Note*\n" << "Removed:\n";
    for (auto& item : mp)
        cout << item.second << " - '" << item.first << "'" << endl;
}


void modify_str(string& str, map<char, unsigned>& mp) {
   
    string first, last;
    stringstream ss(str);
    size_t word_count = 0;
    ss >> first;
    ++word_count;
    while (ss >> last)
        ++word_count;
    if (word_count < 3) {
        str = "";
        return;
    }
    for (size_t i = 0; i < str.size(); ++i) {
        if ((first.find(str[i]) != string::npos) || (last.find(str[i]) != string::npos) 
            || !(isalpha((unsigned char)str[i]))) {
            mp[str[i]]++;
            str.erase(i, 1);
            --i;
        }
    }
}