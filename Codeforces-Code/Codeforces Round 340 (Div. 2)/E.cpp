#include <map>
#include <cmath>
#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 111111;
const int MAXP = 2222222;

int n, m, k, nBlock, a[MAXN];

struct Query{
	int id, l, r;
	long long answer;
	bool operator <(const Query &rhs)const {
		if (l / nBlock < rhs.l / nBlock) return true;
		if (l / nBlock > rhs.l / nBlock) return false;
		int which = l / nBlock;
		if (which & 1) return r < rhs.r;
		else return r > rhs.r;
	}
}q[MAXN];

int cntValue[MAXP];
std::map<int, std::vector<int> > map;
long long counter;

bool cmp(const Query &a, const Query &b) {
	return a.id < b.id;
}

int getNumber(const std::vector<int> &data, int l, int r) {
	l = std::lower_bound(data.begin(), data.end(), l) - data.begin();
	r = std::upper_bound(data.begin(), data.end(), r) - data.begin() - 1;
	return r - l + 1;
}

int main() {
	std::cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		a[i] ^= a[i - 1];
	}
	for (int i = 0; i <= n; i++) {
		map[a[i]].push_back(i);
	}
	for (int i = 1; i <= m; i++) {
		std::cin >> q[i].l >> q[i].r;
		q[i].id = i;
	}
	nBlock = (int)ceil(sqrt(n));
	std::sort(q + 1, q + m + 1);
	cntValue[0] = 1;
	for (int i = 1, l = 1, r = 0; i <= m; i++) {
		for (int j = r + 1; j <= q[i].r; j++) {
			counter += cntValue[a[j] ^ k];
			cntValue[a[j]]++;
		}
		for (int j = r; j > q[i].r; j--) {
			cntValue[a[j]]--;
			counter -= cntValue[a[j] ^ k];
		}
		for (int j = l; j < q[i].l; j++) {
			cntValue[a[j - 1]]--;
			counter -= cntValue[a[j - 1] ^ k];
		}
		for (int j = l - 1; j >= q[i].l; j--) {
			counter += cntValue[a[j - 1] ^ k];
			cntValue[a[j - 1]]++;
		}
		r = q[i].r;
		l = q[i].l;
		q[i].answer = counter;
	}
	std::sort(q + 1, q + m + 1, cmp);
	for (int i = 1; i <= m; i++) {
		std::cout << q[i].answer << std::endl;
	}
	return 0;
}
