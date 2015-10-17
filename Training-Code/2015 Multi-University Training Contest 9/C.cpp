#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 1200101;
const int MaxNode = 1200000;
const int MaxData = 100000;
const int INF = ~0u >> 2;

int n, global, size, c[MAXN][2], f[MAXN], p[MAXN], w[MAXN], d[MAXN], fa[MAXN];
long long answer[MAXN];
std::pair<int, int> e[MAXN];
bool r[MAXN];

int getfa(int x) {
	return fa[x] ? fa[x] = getfa(fa[x]) : x;
}

void pushdown(int x) {
	if (r[x]) {
		std::swap(c[x][0], c[x][1]);
		r[c[x][0]] ^= 1;
		r[c[x][1]] ^= 1;
		r[x] = 0;
	}
}

void update(int x) {
	w[x] = x;
	if (c[x][0] && d[w[c[x][0]]] < d[w[x]]) w[x] = w[c[x][0]];
	if (c[x][1] && d[w[c[x][1]]] < d[w[x]]) w[x] = w[c[x][1]];
}

void rotate(int x, int k) {
	pushdown(x); pushdown(c[x][k]);
	int y = c[x][k]; c[x][k] = c[y][k ^ 1]; c[y][k ^ 1] = x;
	if (f[x] != -1) c[f[x]][c[f[x]][1] == x] = y;
	f[y] = f[x]; f[x] = y; f[c[x][k]] = x; std::swap(p[x], p[y]);
	update(x); update(y);
}

void splay(int x, int s = -1) {
	while (f[x] != s) {
		if (f[f[x]] != s) rotate(f[f[x]], (c[f[f[x]]][1] == f[x]) ^ r[f[f[x]]]);
		rotate(f[x], (c[f[x]][1] == x) ^ r[f[x]]);
	}
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
	r[x] ^= 1;
}

void link(int x, int y) {
	setroot(x);
	p[x] = y;
}

void cut(int x,int y) {
    access(x); splay(y, -1);
    if (p[y] == x) p[y] = -1;
    else {
    	access(y);
    	splay(x, -1);
    	p[x] = -1;
    }
}

int query(int x, int y) {
	setroot(x);
	access(y);
	splay(y);
	return w[y];
}

void addedge(int x, int y, int value) {
	int fx = getfa(x), fy = getfa(y);
	if (fx == fy) {
		int gmin = query(x, y);
		if (value >= d[gmin]) {
			global += value - d[gmin];
			cut(e[gmin].first, gmin);
			cut(e[gmin].second, gmin);
			size++;
			d[size] = value;
			e[size] = std::make_pair(x, y);
			link(x, size);
			link(y, size);
		}
	}
	else{
		size++;
		d[size] = value;
		e[size] = std::make_pair(x, y);
		link(x, size);
		link(y, size);
		fa[fx] = fy;
		global += value;
	}
}

void prepare() {
	std::fill(f + 1, f + MaxNode + 1, -1);
	std::fill(p + 1, p + MaxNode + 1, -1);
	std::fill(d + 1, d + MaxNode + 1, INF);
	for (int i = 1; i <= MaxNode; i++) w[i] = i;
	global = 0;
	size = MaxData;
	for (int i = 2; i <= MaxData; i++) {
		for (int j = 1; j * j <= i; j++) {
			if (i % j) continue;
			addedge(j, i, j);
			if (j * j != i && j != 1) {
				addedge(i / j , i, i / j);
			}
		}
		answer[i] = global;
	}
}

int main() {
	//freopen("input.txt", "r", stdin);
	prepare();
	while (scanf("%d", &n) == 1) {
		printf(LL "\n", answer[n]);
	}
	return 0;
}
