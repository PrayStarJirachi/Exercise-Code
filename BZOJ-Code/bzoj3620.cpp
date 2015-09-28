#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 30001;
const int MAXM = 60001;

int k, len, answer, fail[MAXN];
char s[MAXN];

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%s", s + 1);
	scanf("%d", &k);
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++) {
		char *now = s + (i - 1);
		len = n - i + 1;
		fail[0] = -1;
		now[0] = 0;
		for (int i = 1; i <= len; i++) {
			int p = fail[i - 1];
			while (p != -1 && now[p + 1] != now[i]) {
				p = fail[p];
			}
			fail[i] = p + 1;
		}
		for (int i = 1; i <= len; i++) {
			int p = fail[i];
			while (p << 1 >= i) p = fail[p];
			if (p >= k) answer++;
		}
	}
	printf("%d\n", answer);
	return 0;
}
