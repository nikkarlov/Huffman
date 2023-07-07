#include<iostream>
#include<string>
#include<fstream>
using namespace std;
struct list {
	char zn;
	list* left;
	list* right;
};
list* inp(string& str, long long& ind) {
	list* n_list = new list;
	if (str[ind] == '~') {
		n_list->zn = NULL;
		ind++;
		n_list->left = inp(str, ind);
		ind++;
		n_list->right = inp(str, ind);
	}
	else {
		n_list->zn = str[ind], n_list->left = nullptr, n_list->right = nullptr;
	}
	return n_list;
}
void dec(string& ans, string& str, list* root) {
	list* copy_root = root;
	for (long long i = 0; i < str.size(); i++) {
		if (str[i] == '0') {
			copy_root = copy_root->left;
		}
		else {
			copy_root = copy_root->right;
		}
		if (copy_root->zn != NULL) {
			ans += copy_root->zn;
			copy_root = root;
		}
	}
}
int main() {
	string str, str_haf, ans;
	ifstream fin;
	fin.open("encoded.txt");
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
		{
			str += line;
		}
	}
	fin.close();
	fin.open("tree.txt");
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
		{
			str_haf += line;
			str_haf += '\n';
		}
		str_haf.pop_back();
	}
	fin.close();
	long long ind = 0;
	list* root = inp(str_haf, ind);
	dec(ans, str, root);
	ofstream fout;
	fout.open("decoded.txt");
	fout << ans;
	fout.close();
	return 0;
}