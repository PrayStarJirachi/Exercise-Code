#include <cstdio>
#include <algorithm>

const int MAXN = 1111111;

int n, m, k, tree[MAXN * 5];

void build(int n, int l, int r) {
	if (l == r) {
		tree[n] = 1;
		return;
	}
	build(n << 1, l, l + r >> 1);
	build(n << 1 ^ 1, (l + r >> 1) + 1, r);
	tree[n] = tree[n << 1] + tree[n << 1 ^ 1];
}

int select(int n, int l, int r, int x) {
	if (l == r) return l;
	if (x <= tree[n << 1]) return select(n << 1, l, l + r >> 1, x);
	else return select(n << 1 ^ 1, (l + r >> 1) + 1, r, x - tree[n << 1]);
}

int query(int n, int l, int r, int x, int y) {
	if (r < x || l > y) return 0;
	if (x <= l && r <= y) return tree[n];
	int left = query(n << 1, l, l + r >> 1, x, y);
	int right = query(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
	return left + right;
}

void modify(int n, int l, int r, int x) {
	if (l == r) {
		tree[n] = 0;
		return;
	}
	if (x <= (l + r >> 1)) modify(n << 1, l, l + r >> 1, x);
	else modify(n << 1 ^ 1, (l + r >> 1) + 1, r, x);
	tree[n] = tree[n << 1] + tree[n << 1 ^ 1];
}

int main() {
	freopen("E.in", "r", stdin);
	scanf("%d%d%d", &m, &n, &k);
	build(1, 0, n + m + 1);
	int answer = 0, remain = n + m + 2;
	for (int i = 1; i <= n + m + 1; i++) {
		int where = k % remain, next;
		if (where == 0) where = remain;
		std::pair<int, int> tmp;
		tmp.first = query(1, 0, n + m + 1, answer, n + m + 1);
		tmp.second = query(1, 0, n + m + 1, 0, answer - 1);
		if (where > tmp.first) {
			where -= tmp.first;
			next = select(1, 0, n + m + 1, where);
		}
		else{
			where += tmp.second;
			next = select(1, 0, n + m + 1, where);
		}
		modify(1, 0, n + m + 1, next);
		remain--;
		if (next == 0 || next == m + 1) {
			modify(1, 0, n + m + 1, m + 1 - next);
			remain--;
		}
		answer = next;
	}
	if (answer < m + 1) printf("%d\n", answer);
	else printf("%d\n", m + 1 - answer);
	return 0;
}
