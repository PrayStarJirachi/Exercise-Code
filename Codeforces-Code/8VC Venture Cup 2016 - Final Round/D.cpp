#include <bits/stdc++.h>

typedef long long Int64;

const int MAXN = 210001;

int n, k, a, b, q;
Int64 bit[2][MAXN], c[2][MAXN];

void add(int id, int x, int d) {
	for (int i = x; i <= n; i += i & -i) {
		bit[id][i] += d;
	}
}

Int64 sum(int id, int x) {
	if (x <= 0) return 0;
	Int64 ret = 0;
	for (int i = x; i; i -= i & -i) {
		ret += bit[id][i];
	}
	return ret;
}

void refresh(int id, Int64 base, int pos, Int64 value) {
	Int64 oldValue = sum(id, pos) - sum(id, pos - 1);
	Int64 newValue = std::min(base, c[id][pos] += value);
	add(id, pos, newValue - oldValue);
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n >> k >> a >> b >> q;	
	for (int i = 1; i <= q; i++) {
		int op, pos, value;
		std::cin >> op >> pos;
		if (op == 1) {
			std::cin >> value;
			refresh(0, b, pos, value);
			refresh(1, a, n - pos + 1, value);
		} else {
			Int64 answer = 0;
			answer += sum(0, pos - 1);
			answer += sum(1, n - (pos + k) + 1);
			std::cout << answer << std::endl;
		}
	}
	return 0;
}
