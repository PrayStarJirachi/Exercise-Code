#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>

int n;
std::string no;

int main() {
	std::cin >> n;
	int len = 0;
	for (int i = 1; i <= n; i++) {
		static std::string a;
		std::cin >> a;
		bool check = true;
		if (a == "0") return printf("0"), 0;
		int checkZero = 0, checkOne = 0;
		for (int j = 0; j < (int)a.size(); j++) {
			if (a[j] == '0') checkZero++;
			else if (a[j] == '1') checkOne++;
			else check = false;
		}
		check &= (checkOne == 1);
		if (check) len += a.size() - 1;
		else no = a;
	}
	if (no == "") no = "1";
	std::cout << no;
	for (int i = 0; i < len; i++)
		std::cout << 0;
	return 0;
}
