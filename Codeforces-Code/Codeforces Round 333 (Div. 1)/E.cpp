#include <cstdio>
#include <vector>
#include <algorithm>

const int MAXN = 5555;
const int MAXQ = 33333;
const int MAXK = 1111;
const int POW = 10000019;
const int MOD = 1000000007;
const int MAXL = 22;

int n, m, k, M, cnt, rem[MAXL][MAXN], answer[(MAXN + MAXQ) * 4], dp[MAXK], hash[MAXN + MAXQ];
std::vector<int> query;
std::pair<int, int> o[MAXN + MAXQ];
std::vector<std::pair<int, int> > tree[(MAXN + MAXQ) * 4];
bool flag[(MAXN + MAXQ) * 4];

int getSum(int x, int y) {
	int left = std::lower_bound(query.begin(), query.end(), x) - query.begin() - 1;
	int right = std::upper_bound(query.begin(), query.end(), y) - query.begin() - 1;
	return right - left;
}

void cover(int x, int y, const std::pair<int, int> &data) {
	for (x += M - 1, y += M + 1; x ^ y ^ 1; x >>= 1, y >>= 1) {
		if (x & 1 ^ 1) tree[x ^ 1].push_back(data);
		if (y & 1) tree[y ^ 1].push_back(data);
	}
}

void dfs(int h, int x, int l, int r) {
	if (getSum(l, r) == 0) return;
	for (int i = 0; i <= k; i++) rem[h][i] = dp[i];
	for (int i = 0; i < (int)tree[x].size(); i++) {
		std::pair<int, int> now = tree[x][i];
		for (int j = k; j >= now.second; j--)
			dp[j] = std::max(dp[j], dp[j - now.second] + now.first);
	}
	if (l == r) {
		for (int i = 1, tmp = 1; i <= k; i++) {
			answer[x] = (answer[x] + 1ll * dp[i] * tmp % MOD) % MOD;
			tmp = 1ll * tmp * POW % MOD;
		}
	}
	else{
		dfs(h + 1, x << 1, l, l + r >> 1);
		dfs(h + 1, x << 1 ^ 1, (l + r >> 1) + 1, r);
	}
	for (int i = 0; i <= k; i++) dp[i] = rem[h][i];
}

int main() {
	freopen("E.in", "r", stdin);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		cnt++;
		scanf("%d%d", &o[cnt].first, &o[cnt].second);
		hash[cnt] = i;
	}
	scanf("%d", &m);
	for (M = 1; M <= (n + m) + 1; M <<= 1);
	for (int i = 1; i <= m; i++) {
		int op, value, mass, id;
		scanf("%d", &op);
		if (op == 1) {
			cnt++;
			scanf("%d%d", &o[cnt].first, &o[cnt].second);
			hash[cnt] = n + i;
		} else if (op == 2) {
			scanf("%d", &id);
			cover(hash[id], n + i, o[id]);
			hash[id] = 0;
		} else if (op == 3) {
			query.push_back(n + i);
			flag[M + n + i] = true;
		}
	}
	for (int i = 1; i <= cnt; i++) {
		if (!hash[i]) continue;
		cover(hash[i], n + m, o[i]);
	}
	dfs(0, 1, 0, M - 1);
	for (int i = 0; i < (int)query.size(); i++) {
		printf("%d\n", answer[M + query[i]]);
	}
	return 0;
}
