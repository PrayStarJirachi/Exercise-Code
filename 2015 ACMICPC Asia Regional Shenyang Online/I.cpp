#include <map>
#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 60001;
const int MAXM = 200001;
const int MAXQ = 200001;

struct Road{
	int x, y;
	bool flag;
}r[MAXM];

struct Query{
	int op, x, y, answer;
}w[MAXQ];

int T, n, m, q, size, f[MAXN], p[MAXN], c[MAXN][2], s[MAXN], zsum[MAXN], d[MAXN];
bool rev[MAXN], flag[MAXN];
std::map<std::pair<int, int>, int> map;

void makesame(int x) {
	if (!x) return;
	zsum[x] = d[x] = 0;
	flag[x] = true;
}

void pushdown(int x) {
	if (!x) return;
	if (rev[x]) {
		std::swap(c[x][0], c[x][1]);
		rev[c[x][0]] ^= 1;
		rev[c[x][1]] ^= 1;
		rev[x] = 0;
	}
	if (flag[x]) {
		if (c[x][0]) makesame(c[x][0]);
		if (c[x][1]) makesame(c[x][1]);
		flag[x] = 0;
	}
}

void update(int x) {
	if (!x) return;
	zsum[x] = d[x];
	s[x] = 1;
	if (c[x][0]) {
		zsum[x] += zsum[c[x][0]];
		s[x] += s[c[x][0]];
	}
	if (c[x][1]) {
		zsum[x] += zsum[c[x][1]];
		s[x] += s[c[x][1]];
	}
}

void rotate(int x, int k) {
	pushdown(x); pushdown(c[x][k]);
	int y = c[x][k]; c[x][k] = c[y][k ^ 1]; c[y][k ^ 1] = x;
	if (f[x] != -1) c[f[x]][c[f[x]][1] == x] = y;
	f[y] = f[x]; f[x] = y; f[c[x][k]] = x; std::swap(p[x], p[y]);
	update(x); update(y);
}

void splay(int x, int s = -1) {
	pushdown(x);
	while (f[x] != s) {
		if (f[f[x]] != s) rotate(f[f[x]], (c[f[f[x]]][1] == f[x]) ^ rev[f[f[x]]]);
		rotate(f[x], (c[f[x]][1] == x) ^ rev[f[x]]);
	}
	update(x);
}

void access(int x) {
	int y = 0;
	while (x != -1) {
		splay(x); pushdown(x);
		f[c[x][1]] = -1; p[c[x][1]] = x;
		c[x][1] = y; f[y] = x; p[y] = -1;
		update(x); x = p[y = x];
	}
}

void setroot(int x) {
	access(x);
	splay(x);
	rev[x] ^= 1;
}

int getfa(int x) {
	access(x); splay(x); pushdown(x);
	for (; c[x][0]; x = c[x][0]) pushdown(x);
	return x;
}

void link(int x, int y) {
	setroot(x);
	p[x] = y;
}

void connect(int x, int y) {
	if (getfa(x) == getfa(y)) {
		setroot(x);
		access(y);
		splay(y);
		makesame(y);
	}
	else{
		size++;
		d[size] = 1;
		link(x, size);
		link(y, size);
	}
}

int query(int x, int y) {
	setroot(x);
	access(y);
	splay(y);
	return zsum[y];
}

int main() {
	freopen("I.in", "r", stdin);
	freopen("I.out", "w", stdout);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d%d%d", &n, &m, &q);
		map.clear();
		for (int i = 1; i <= m; i++) {
			scanf("%d%d", &r[i].x, &r[i].y);
			if (r[i].x > r[i].y) std::swap(r[i].x, r[i].y);
			map[std::make_pair(r[i].x, r[i].y)]++;
		}
		for (int i = 1; i <= q; i++) {
			scanf("%d%d%d", &w[i].op, &w[i].x, &w[i].y);
			if (w[i].x > w[i].y) std::swap(w[i].x, w[i].y);
			if (w[i].op == 1) {
				map[std::make_pair(w[i].x, w[i].y)]--;
			}
		}
		size = n;
		std::fill(f + 1, f + 2 * n + 1, -1);
		std::fill(p + 1, p + 2 * n + 1, -1);
		std::fill(s + 1, s + 2 * n + 1, 1);
		std::fill(d + 1, d + 2 * n + 1, 0);
		std::fill(flag + 1, flag + 2 * n + 1, false);
		std::fill(rev + 1, rev + 2 * n + 1, false);
		std::fill(zsum + 1, zsum + 2 * n + 1, 0);
		for (int i = 1; i <= 2 * n; i++) {
			c[i][0] = c[i][1] = 0;
		}
		for (int i = 1; i <= m; i++) {
			int cnt = map[std::make_pair(r[i].x, r[i].y)]--;
			for (int j = 1; j <= cnt; j++) {
				connect(r[i].x, r[i].y);
			}
		}
		for (int i = q; i >= 1; i--) {
			if (w[i].op == 1) {
				connect(w[i].x, w[i].y);
			}
			else{
				w[i].answer = query(w[i].x, w[i].y);
			}
		}
		printf("Case #%d:\n", cs);
		for (int i = 1; i <= q; i++) {
			if (w[i].op == 2) {
				printf("%d\n", w[i].answer);
			}
		}
	}
	return 0;
}
