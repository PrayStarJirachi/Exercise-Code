#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 2000001;
const int MAXT = 4000001;
const int MAXS = 4000001;
const long long INF = 1ll << 50;

int T, A, B, last, size, p, c[MAXT][26], l[MAXT], f[MAXT], w[MAXN];
long long dp[MAXN];
char s[MAXN];

struct Segment_Tree{
	int M;
	long long d[MAXS];
	void init(int n) {
		for (M = 1; M <= n + 1; M <<= 1);
		for (int i = 1; i <= M + n; i++) d[i] = INF;
	}
	void modify(int x, long long v) {
		x += M;
		d[x] = std::min(d[x], v);
		for (x >>= 1; x; x >>= 1) {	
			d[x] = std::min(d[x << 1], d[x << 1 ^ 1]);
		}
	}
	long long query(int x, int y) {
		long long ret = INF;
		if (x > y) return ret;
		for (x += M - 1, y += M + 1; x ^ y ^ 1; x >>= 1, y >>= 1) {
			if (x & 1 ^ 1) ret = std::min(ret, d[x ^ 1]);
			if (y & 1) ret = std::min(ret, d[y ^ 1]);
		}
		return ret;
	}
}tree;

int alloc() {
	size++;
	for (int i = 0; i < 26; i++) c[size][i] = 0;
	l[size] = f[size] = 0;
	return size;
}

void add(int x, int &last) {
	int lastnode = last, newnode = alloc(); l[newnode] = l[lastnode] + 1;
	for (; lastnode && !c[lastnode][x]; lastnode = f[lastnode]) c[lastnode][x] = newnode;
	if (!lastnode) f[newnode] = 1;
	else{
		int nownode = c[lastnode][x];
		if (l[nownode] == l[lastnode] + 1) f[newnode] = nownode;
		else{
			int auxnode = alloc(); l[auxnode] = l[lastnode] + 1;
			if (p == nownode) p = auxnode;
			for (int i = 0; i < 26; i++) c[auxnode][i] = c[nownode][i];
			f[auxnode] = f[nownode]; f[nownode] = f[newnode] = auxnode;
			for (; lastnode && c[lastnode][x] == nownode; lastnode = f[lastnode]) c[lastnode][x] = auxnode;
		}
	}
	last = newnode;
}

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%s", s + 1);
		for (int i = 0; i < 26; i++) scanf("%d", w + i);
		scanf("%d%d", &A, &B);
		size = 0;
		last = alloc();
		int n = strlen(s + 1), len = 0;
		tree.init(n); p = 1;
		for (int i = 1, j = 0; i <= n; i++) {
			dp[i] = dp[i - 1] + w[s[i] - 'a'];
			while (j < i - 1 && !c[p][s[i] - 'a']) {
				add(s[++j] - 'a', last);
				if (p != 1 && --len == l[f[p]]) p = f[p];
			}
			if (c[p][s[i] - 'a']) {
				long long tmp = tree.query(j, i - 1);
				tmp = tmp + (long long)i * A;
				tmp = tmp + 2ll * B;
				dp[i] = std::min(dp[i], tmp);
				len++;
				p = c[p][s[i] - 'a'];
			}
			else{
				add(s[++j] - 'a', last);
				p = 1; len = 0;
			}
			tree.modify(i, dp[i] - (long long)i * A);
		}
		printf("Case #%d: " LL "\n", cs, dp[n]);
	}
	return 0;
}
