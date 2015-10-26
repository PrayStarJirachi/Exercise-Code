#include <cstdio>
#include <algorithm>

const int MAXN = 501;

int n, a[MAXN], q[MAXN], answer[MAXN], o[MAXN];
bool map[MAXN][MAXN], v[MAXN];
char s[MAXN];

int main(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s + 1);
		for (int j = 1; j <= n; j++)
			if (s[j] == '1') map[i][j] = true;
	}
	for (int i = 1; i <= n; i++) {
		if (v[i]) continue;
		int left = 0, right = 0;
		v[q[++right] = i] = true;
		while (left < right) {
			left++;
			for (int j = 1; j <= n; j++)
				if (map[q[left]][j] && !v[j]) {
					v[q[++right] = j] = true;
				}
		}
		for (int j = 1; j <= right; j++) {
			o[j] = a[q[j]];
		}
		std::sort(o + 1, o + right + 1);
		std::sort(q + 1, q + right + 1);
		for (int j = 1; j <= right; j++) answer[q[j]] = o[j];
	}
	for (int i = 1; i <= n; i++) printf("%d%c", answer[i], " \n"[i == n]);
	return 0;
}
