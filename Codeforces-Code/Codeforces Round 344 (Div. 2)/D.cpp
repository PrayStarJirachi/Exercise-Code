#include <bits/stdc++.h>

const int MAXN = 210001;

int n, m, fail[MAXN], lA[MAXN], lB[MAXN];
char cA[MAXN], cB[MAXN];
std::pair<long long, char> dA[MAXN], dB[MAXN];

int main() {
	int tn, tm;
	std::cin >> tn >> tm;
	for (int i = 1; i <= tn; i++) {
		scanf("%d-%c", lA + i, &cA[i]);
		dA[++n] = std::make_pair(lA[i], cA[i]);
		if (n > 1 && dA[n].second == dA[n - 1].second) {
			dA[n - 1].first += dA[n].first;
			n--;
		}
	}
	for (int i = 0; i < tm; i++) {
		scanf("%d-%c", lB + i, &cB[i]);
		dB[m++] = std::make_pair(lB[i], cB[i]);
		if (m > 1 && dB[m - 2].second == dB[m - 1].second) {
			dB[m - 2].first += dB[m - 1].first;
			m--;
		}
	}
	if (m == 1) {
		long long answer = 0;
		for (int i = 1; i <= n; i++) {
			if (dA[i].second != dB[0].second) continue;
			answer += std::max(0ll, dA[i].first - dB[0].first + 1);
		}
		std::cout << answer << std::endl;
		return 0;
	}
	if (m == 2) {
		long long answer = 0;
		for (int i = 1; i < n; i++) {
			if (dA[i].second != dB[0].second || dA[i + 1].second != dB[1].second) continue;
			if (dA[i].first < dB[0].first || dA[i + 1].first < dB[1].first) continue;
			answer++;
		}
		std::cout << answer << std::endl;
		return 0;
	}
	fail[0] = -1;
	for (int i = 1; i < m - 1; i++) {
		int p = fail[i - 1];
		while (p != -1 && (p + 1 > m - 2 || dB[i] != dB[p + 1])) p = fail[p];
		fail[i] = p + 1;
	}
	int answer = 0;
	for (int i = 1, z = 0; i <= n; i++) {
		while (z != -1 && (z + 1 > m - 2 || dA[i] != dB[z + 1])) z = fail[z];
		z++;
		if (z == m - 2) {
			if (dA[i - (m - 2)].second == dB[0].second && dA[i + 1].second == dB[m - 1].second) {
				if (dA[i - (m - 2)].first >= dB[0].first && dA[i + 1].first >= dB[m - 1].first) {
					answer++;
				}
			}
		}
	}
	std::cout << answer << std::endl;
	return 0;
}
