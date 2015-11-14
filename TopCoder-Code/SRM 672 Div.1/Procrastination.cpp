#include <map>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

const long long INF = 1ll << 60;

template <typename Type> Type getmin(Type &a, const Type &b) {return (a > b) ? (a = b) : a;}
template <typename Type> Type getmax(Type &a, const Type &b) {return (a < b) ? (a = b) : a;}

class Procrastination{
private:
	std::vector<long long> divisor[40];
public:
	long long findFinalAssignee(long long n) {
		long long ret = 0, time = 1;
		for (int i = -20; i < 20; i++) {
			long long now = i + n;
			for (long long j = 2; j * j <= now; j++) {
				if (now % j) continue;
				divisor[i + 20].push_back(j);
				if (j * j != now) divisor[i + 20].push_back(now / j);
			}
			std::sort(divisor[i + 20].begin(), divisor[i + 20].end());
		}
		while (true) {
			int curpos = -1, prepos = -1;
			curpos = std::upper_bound(divisor[ret + 20].begin(), divisor[ret + 20].end(), time) - divisor[ret + 20].begin();
			if (curpos == divisor[ret + 20].size()) curpos = -1;
			prepos = std::upper_bound(divisor[ret - 1 + 20].begin(), divisor[ret - 1 + 20].end(), time) - divisor[ret - 1 + 20].begin();
			if (prepos == (int)divisor[ret - 1 + 20].size()) prepos = -1;
			if (curpos == -1 && prepos == -1) break;
			long long next = ret;
			if (prepos == -1 || (curpos != -1 && divisor[ret + 20][curpos] < divisor[ret - 1 + 20][prepos])) {
				time = divisor[ret + 20][curpos];
				next++;
			}
			if (curpos == -1 || (prepos != -1 && divisor[ret - 1 + 20][prepos] < divisor[ret + 20][curpos])) {
				time = divisor[ret - 1 + 20][prepos];
				next--;
			}
			ret = next;
		}
		return n + ret;
	}
}T;

long long n;

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> n;
	std::cout << T.findFinalAssignee(n) << std::endl;
	return 0;
}
