#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 1000101;

struct Interval{
	int l, r;
	bool operator <(const Interval &rhs)const {
		return r - l + 1 < rhs.r - rhs.l + 1;
	}
}s[MAXN];

struct Query{
	int data, id;
	long long answer;
	bool operator <(const Query &rhs)const {
		return data < rhs.data;
	}
}q[MAXN];

struct Segment_Tree{
	int nSize;
	long long *tree;
	int init(int n, long long *d) {
		nSize = n;
		tree = d;
		for (int i = 1; i <= n; i++) tree[i] = 0;
	}
	void insert(int x, int d) {
		for (int i = x; i <= nSize; i += i & -i) {
			tree[i] += d;
		}
	}
	long long query(int x, int y) {
		long long ret = 0;
		if (x > y) return ret;
		for (int i = y; i; i -= i & -i) ret += tree[i];
		for (int i = x - 1; i; i -= i & -i) ret -= tree[i];
		return ret;
	}
}t;

int n, m, nS;
long long h[MAXN];

bool cmp(const Query &a, const Query &b) {
	return a.id < b.id;
}

int main() {
int used = sizeof(h) + sizeof(t) + sizeof(q) + sizeof(s);
printf("%d\n", used / 1048576);
	freopen("C.in", "r", stdin);
	while (scanf("%d", &n) == 1) {
		if (n == 0) break;
		for (int i = 1; i <= n; i++) scanf("%d", &q[i].data);
		nS = 0;
		std::fill(h, h + 1000000 + 1, 0);
		for (int i = 1; i <= n; i++) {
			if (h[q[i].data]) s[++nS] = (Interval){h[q[i].data], i};
			h[q[i].data] = i;
		}
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) {
			scanf("%d", &q[i].data);
			q[i].id = i;
			q[i].answer = 0;
		}
		std::sort(q + 1, q + m + 1);
		std::sort(s + 1, s + nS + 1);
		for (int i = 1, p = 1; i <= m; i++) {
			while (p <= nS && s[p].r - s[p].l + 1 <= q[i].data) p++;
			q[i].answer += -(p - 1);
		}
		t.init(n, h);
		for (int i = 1, p = 1; i <= m; i++) {
			while (p <= nS && s[p].r - s[p].l + 1 <= q[i].data) {
				t.insert(s[p].l, s[p].l);
				p++;
			}
			long long tmp1, tmp2;
			tmp1 = t.query(1, n - q[i].data + 1);
			tmp2 = t.query(n - q[i].data + 2, n);
			long long lmax = tmp1;
			q[i].answer += -lmax;
		}
		t.init(n, h);
		for (int i = 1, p = 1; i <= m; i++) {
			while (p <= nS && s[p].r - s[p].l + 1 <= q[i].data) {
				t.insert(s[p].l, 1);
				p++;
			}
			long long tmp1, tmp2;
			tmp1 = t.query(1, n - q[i].data + 1);
			tmp2 = t.query(n - q[i].data + 2, n);
			long long lmax = 1ll * tmp2 * (n - q[i].data + 1);
			q[i].answer += -lmax;
		}
		t.init(n, h);
		for (int i = 1, p = 1; i <= m; i++) {
			while (p <= nS && s[p].r - s[p].l + 1 <= q[i].data) {
				t.insert(s[p].r, s[p].r);
				p++;
			}
			long long tmp1, tmp2;
			tmp1 = t.query(q[i].data, n);
			tmp2 = t.query(1, q[i].data - 1);
			long long lmin = tmp1;
			q[i].answer += lmin;
		}
		t.init(n, h);
		for (int i = 1, p = 1; i <= m; i++) {
			while (p <= nS && s[p].r - s[p].l + 1 <= q[i].data) {
				t.insert(s[p].r, 1);
				p++;
			}
			long long tmp1, tmp2;
			tmp1 = t.query(q[i].data, n);
			tmp2 = t.query(1, q[i].data - 1);
			long long lmin = tmp2 - 1ll * tmp1 * (q[i].data - 1);
			q[i].answer += lmin;
		}
		std::sort(q + 1, q + m + 1, cmp);
		for (int i = 1; i <= m; i++)
			printf(LL "\n", 1ll * (n - q[i].data + 1) * q[i].data + q[i].answer);
	}
	return 0;
}
