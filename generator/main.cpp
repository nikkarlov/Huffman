#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
using namespace std;
struct list {
	char zn;
	long long c;
	list* next;
	list* left;
	list* right;
};
void sort(list*& L) {
	bool fl = 1;
	for (long long i = 0; fl; i++) {
		list* q = L;
		fl = 0;
		while (q->next != nullptr) {
			if (q->c > q->next->c) {
				fl = 1;
				char a = q->zn;
				long long b = q->c;
				q->c = q->next->c;
				q->zn = q->next->zn;
				q->next->zn = a;
				q->next->c = b;
			}
			q = q->next;
		}
	}
}
void stat(string& str, list*& root) {
	for (long long i = 0; i < str.size(); i++) {
		bool fl = 1;
		list* root_copy = root;
		while (root_copy != nullptr) {
			if (root_copy->zn == str[i]) {
				root_copy->c++;
				fl = 0;
				break;
			}
			root_copy = root_copy->next;
		}
		if (fl) {
			list* n_list = new list;
			n_list->zn = str[i], n_list->c = 1, n_list->next = nullptr, n_list->left = nullptr, n_list->right = nullptr;
			root_copy = root;
			root = n_list;
			root->next = root_copy;
		}
	}
	sort(root);
}
void build_haf(list*& root) {
	while (root->next != nullptr) {
		list* n_list = new list;
		n_list->zn = NULL, n_list->c = root->c + root->next->c, n_list->next = root->next->next, n_list->left = root, n_list->right = root->next;
		root = n_list;
		list* root_copy = root;
		while (root_copy->next != nullptr) {
			if (root_copy->c > root_copy->next->c) {
				char a = root_copy->zn;
				long long b = root_copy->c;
				list* c = root_copy->left;
				list* d = root_copy->right;
				root_copy->c = root_copy->next->c;
				root_copy->zn = root_copy->next->zn;
				root_copy->left = root_copy->next->left;
				root_copy->right = root_copy->next->right;
				root_copy->next->zn = a;
				root_copy->next->c = b;
				root_copy->next->left = c;
				root_copy->next->right = d;
			}
			else {
				break;
			}
			root_copy = root_copy->next;
		}
	}
}
void outp(list* root, string& ans) {
	if (root->zn == NULL) {
		ans.push_back('~');
		outp(root->left, ans);
		outp(root->right, ans);
	}
	else {
		ans.push_back(root->zn);
	}
}
void detour(list* root, map<char, string>& code_s, string buf) {
	if (root->zn == NULL) {
		buf += '0';
		detour(root->left, code_s, buf);
		buf.pop_back();
		buf += '1';
		detour(root->right, code_s, buf);
		buf.pop_back();
	}
	else {
		code_s[root->zn] = buf;
	}
}
int main() {
	string str, ans;
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
	list* root = nullptr;
	stat(str, root);
	build_haf(root);
	outp(root, ans);
	detour(root, code_s, "");
	ofstream fout;
	fout.open("tree.txt");
	fout << ans << endl;
	fout.close();
	fout.open("table.txt");
	for (map<char, string>::iterator itt = code_s.begin(); itt != code_s.end(); itt++) {
		fout << itt->first << " " << itt->second << endl;
	}
	fout.close();
	return 0;
}