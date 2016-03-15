#include <bits/stdc++.h>

const int MAXN = 4001;

int r, c, n, k, a[MAXN], p[MAXN], L[MAXN], R[MAXN], sA[MAXN], sB[MAXN], pA[MAXN], pB[MAXN];
std::pair<int, int> z[MAXN];
std::vector<int> d[MAXN];
long long answer;

bool cmp(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	return a.second < b.second;
}

void del(int now, long long &answer) {
	int tA = 0, tB = 0, zL = now, zR = now;
	if (!--a[now]) {
		R[L[now]] = R[now];
		L[R[now]] = L[now];
	}
	for (int i = 1; i <= k + 1 && zL != 0; i++, zL = L[zL]) {
		sA[++tA] = a[zL];
		pA[tA] = zL;
	}
	for (int i = 1; i <= k + 1 && zR != c + 1; i++, zR = R[zR]) {
		sB[++tB] = a[zR];
		pB[tB] = zR;
	}
	for (int i = 1; i <= tA; i++) sA[i] += sA[i - 1];
	for (int i = 1; i <= tB; i++) sB[i] += sB[i - 1];
	for (int i = tA, j = 1; i >= 1; i--) {
		while (j <= tB && sA[i] + sB[j] - a[now] + 1 < k) j++;
		if (j <= tB && sA[i] + sB[j] - a[now] + 1 == k) {
			int pred = (i == tA) ? 0 : pA[i + 1];
			int succ = (j == tB) ? c + 1 : pB[j + 1];
			answer += 1ll * (pA[i] - pred) * (succ - pB[j]);
			assert(pA[i] >= pred);
		}
	}
	//puts("");
}

int main() {
	freopen("G.in", "r", stdin);
	std::cin >> r >> c >> n >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> z[i].first >> z[i].second;
	}
	std::sort(z + 1, z + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		d[z[i].first].push_back(i);
	}
	long long base = 0;
	for (int i = 1; i <= r; i++)
		for (int j = 1; j <= c; j++)
			base += 1ll * i * j;
	for (int i = 1; i <= r; i++) {
		int tot = 0;
		R[0] = c + 1;
		L[c + 1] = 0;
		static int tmp[MAXN], cnt[MAXN];
		std::fill(tmp, tmp + c + 1, 0);
		std::fill(a, a + c + 1, 0);
		std::fill(cnt, cnt + n + 1, 0);
		for (int j = n; j >= 1; j--) {
			if (z[j].first < i) continue;
			if (a[z[j].second] == 0) {
				p[j] = z[j].second;
				L[z[j].second] = 0;
				R[z[j].second] = R[0];
				L[R[0]] = z[j].second;
				R[0] = z[j].second;
			}
			a[z[j].second]++;
			tmp[z[j].second]++;
		}
		long long counter = 0;
		for (int j = 1; j <= c; j++) {
			tmp[j] += tmp[j - 1];
		}
		for (int j = 1; j <= c; j++) {
			cnt[tmp[j - 1]]++;
			for (int h = 0; h < k && h <= tmp[j]; h++) {
				counter += cnt[tmp[j] - h];
			}
		}
		for (int j = r; j >= i; j--) {
			answer -= counter;
			//std::cout << "(" << i << ", " << j << ") = " << counter << std::endl;
			for (auto v : d[j]) {
				del(z[v].second, counter);
			}
			//std::cout << "After = " << counter << std::endl;
		}
	}
	//std::cout << base << std::endl;
	//std::cout << -answer << std::endl;
	std::cout << base + answer << std::endl;
	return 0;
}
