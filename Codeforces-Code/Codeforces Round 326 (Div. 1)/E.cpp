#include <cstdio>
#include <algorithm>

const int MAXL = 32;
const int MAXLOG = 32;
const int MAXN = 222222;

struct Node{
	int d[MAXL];
	Node() {
		std::fill(d, d + MAXLOG, 0);
	}
	Node(int a) {
		std::fill(d, d + MAXLOG, 0);
		d[0] = a;
	}
	int getAnswer() {
		int ret = 0;
		for (int i = 0; i < MAXLOG; i++) ret += (d[i] != 0);
		return 1 << ret;
	}
	Node operator +(const Node &rhs)const {
		Node ret;
		static int tmp[MAXLOG * 2];
		for (int i = 0; i < MAXLOG; i++) tmp[i] = d[i];
		for (int i = 0; i < MAXLOG; i++) tmp[MAXLOG + i] = rhs.d[i];
		for (int h = 0; h < MAXLOG; h++) {
			for (int i = h + 1; i < 2 * MAXLOG; i++)
				if (tmp[i] & (1 << h)) {
					std::swap(tmp[i], tmp[h]);
					break;
				}
			if ((tmp[h] & (1 << h)) == 0) continue;
			for (int i = h + 1; i < 2 * MAXLOG; i++)
				if (tmp[i] & (1 << h)) tmp[i] ^= tmp[h];
		}
		for (int i = 0; i < MAXLOG; i++) ret.d[i] = tmp[i];
		return ret;
	}
}tree[MAXN * 4];

int n, m, M, a[MAXN], b[MAXN], bit[MAXN];

void add(int x, int d) {
	for (int i = x; i <= n; i += i & -i) {
		bit[i] ^= d;
	}
}

int query(int x) {
	int ret = 0;
	for (int i = x; i; i -= i & -i) ret ^= bit[i];
	return ret;
}

Node query(int x, int y) {
	Node ret = Node();
	for (x += M - 1, y += M + 1; x ^ y ^ 1; x >>= 1, y >>= 1) {
		if (x & 1 ^ 1) ret = ret + tree[x ^ 1];
		if (y & 1) ret = ret + tree[y ^ 1];
	}
	return ret;
}

void modify(int x, int d) {
	int value = b[x] ^= d;
	for (tree[x += M] = Node(value), x >>= 1; x; x >>= 1) {
		tree[x] = tree[x << 1] + tree[x << 1 ^ 1];
	}
}

int main() {
	freopen("E.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) b[i] = a[i] ^ a[i - 1];
	for (M = 1; M <= n + 1; M <<= 1);
	for (int i = 1; i <= n; i++)
		tree[M + i] = Node(b[i]);
	for (int i = M; i >= 1; i--) {
		tree[i] = tree[i << 1] + tree[i << 1 ^ 1];
	}
	for (int i = 1; i <= m; i++) {
		int op, l, r, k;
		scanf("%d%d%d", &op, &l, &r);
		if (op == 1) {
			scanf("%d", &k);
			modify(l, k);
			modify(r + 1, k);
			add(l, k);
			add(r + 1, k);
		} else {
			Node ret = query(l + 1, r) + Node(a[l] ^ query(l));
			printf("%d\n", ret.getAnswer());
		}
	}
	return 0;
}
