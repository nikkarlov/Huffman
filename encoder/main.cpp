#include<iostream>
#include<string>
#include<map>
#include<fstream>
using namespace std;
struct list {
	char zn;
	list* left;
	list* right;
};
void enc(string& ans, string& str, map<char, string>& code_s) {
	for (long long i = 0; i < str.size(); i++) {
		ans += code_s[str[i]];
	}
}
int main() {
	string str, str_haf, ans;
	map<char, string> code_s;
	ifstream fin;
	fin.open("input.txt");
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
		{
			str += line;
			str += '\n';
		}
		str.pop_back();
	}
	fin.close();
	fin.open("table.txt");
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
		{
			if (line == "") {
				getline(fin, line);
				code_s['\n'] = line.substr(1, line.size() - 1);
			}
			else {
				code_s[line[0]] = line.substr(2, line.size() - 1);
			}
		}
	}
	fin.close();
	long long ind = 0;
	enc(ans, str, code_s);
	ofstream fout;
	fout.open("encoded.txt");
	fout << ans;
	fout.close();
	return 0;
}