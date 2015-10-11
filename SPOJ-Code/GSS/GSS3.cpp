#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 100001;
const long long INF = 1ll << 40;

struct Node{
	long long asum, lsum, rsum, zsum;
	Node() {
		asum = 0;
		lsum = -INF;
		rsum = -INF;
		zsum = -INF;
	}
	Node(int d) : asum(d), lsum(d), rsum(d), zsum(d) {}
	Node operator +(const Node &rhs)const {
		Node ret;
		ret.asum = asum + rhs.asum;
		ret.lsum = std::max(lsum, asum + rhs.lsum);
		ret.rsum = std::max(rsum + rhs.asum, rhs.rsum);
		ret.zsum = std::max(zsum, rhs.zsum);
		ret.zsum = std::max(ret.zsum, rsum + rhs.lsum);
		return ret;
	}
}tree[MAXN * 4];

int n, q, M;

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for (M = 1; M <= n + 1; M <<= 1);
	for (int i = 1; i <= n; i++) {
		int x; scanf("%d", &x);
		tree[M + i] = Node(x);
	}
	for (int i = M; i >= 1; i--) {
		tree[i] = tree[i << 1] + tree[i << 1 ^ 1];
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 0) {
			for (tree[x += M] = Node(y), x >>= 1; x; x >>= 1) {
				tree[x] = tree[x << 1] + tree[x << 1 ^ 1];
			}
		}
		else{
			Node left = Node(), right = Node();
			for (x += M - 1, y += M + 1; x ^ y ^ 1; x >>= 1, y >>= 1) {
				if (x & 1 ^ 1) left = left + tree[x ^ 1];
				if (y & 1) right = tree[y ^ 1] + right;
			}
			Node answer = left + right;
			printf(LL "\n", answer.zsum);
		}
	}
	return 0;
}
