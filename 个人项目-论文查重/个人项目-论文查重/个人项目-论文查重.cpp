#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
using namespace std;
double check(wstring &s, wstring &t) {
	int n = s.length(), m = t.length();

	map<wchar_t, vector<int>> pos;

	for (int i = 0; i < n; ++i) {
		pos[s[i]].emplace_back(i);
	}
	//记录每个字符出现位置
	vector<int> arr;
	for (int i = 0; i < m; ++i) {
		if (pos.count(t[i])) {
			for (auto it = pos[t[i]].rbegin(); it != pos[t[i]].rend(); ++it) {
				arr.emplace_back(*it);
			}
		}
	}
	//遍历另一字符串 将同字符的位置倒序插入
	if (arr.empty()) return 0.0;
	//若无相同字符 则为空 返回 0
	vector<int> res = { arr[0] };
	for (int i = 1; i < arr.size(); ++i) {
		if (arr[i] > res.back()) {
			res.emplace_back(arr[i]);
		}
		else {
			*lower_bound(res.begin(), res.end(), arr[i]) = arr[i];
		}
	}
	//二分查找优化的方法求最长上升子序列
	return res.size() * 1.0 / max(n, m);
}
void init() {
	// init.
	ios::sync_with_stdio(false);  // Linux gcc.
	locale::global(locale("zh_CN.UTF-8"));
	setlocale(LC_CTYPE, "zh_CN.UTF-8");  // MinGW gcc.
	wcout.imbue(locale("zh_CN.UTF-8"));
}
bool readFile(char *filePath, wstring &s) {
	wifstream file;
	file.open(filePath);
	if (!file.is_open()) return false;
	file.imbue(locale("zh_CN.UTF-8"));
	wstring value;
	while (!file.eof()) {
		file >> value;
		s += value;
	}
	return true;
}
int main(int argc, char *argv[]) {
	clock_t time_start, time_end;
	time_start = clock();

	init();
	if (argc < 4) {
		cout << "Please enter 3 paths in Command!" << endl;
		system("pause");
		return 0;
	}

	wstring s, t;
	if (!readFile(argv[1], s)) {
		cout << "First path invalid!" << endl;
		system("pause");
		return 0;
	}
	if (!readFile(argv[2], t)) {
		cout << "Second path invalid!" << endl;
		system("pause");
		return 0;
	}
	
	ofstream outFile;
	outFile.open(argv[3]);

	if (!outFile) {
		cout << "Thrid path invalid!" << endl;
		system("pause");
		return 0;
	}
	outFile << setiosflags(ios::fixed) << setprecision(2);
	outFile << check(s, t) << endl;

	time_end = clock();
	double endtime = (double)(time_end - time_start) / CLOCKS_PER_SEC;
	cout << "Total time:" << endtime * 1000 << "ms" << endl;

	system("pause");
	return 0;
}
