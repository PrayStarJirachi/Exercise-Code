#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXN = 501;
const int MAXM = 1001;

int n, m, w[MAXN], b[MAXM], o[MAXN];
bool v[MAXN];

int main(void) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", w + i);
	for (int i = 1; i <= m; i++) scanf("%d", b + i);
	int tot = 0;
	for (int i = 1; i <= m; i++)
		if (!v[b[i]]) v[o[++tot] = b[i]] = true;
	for (int i = 1; i <= n; i++)
		if (!v[i]) o[++tot] = i;
	long long answer = 0;
	for (int i = 1; i <= m; i++) {
		long long tmp = 0;
		for (int j = 1; j <= n; j++) {
			if (o[j] == b[i]) {
				for (int k = j; k >= 2; k--) o[k] = o[k - 1];
				o[1] = b[i];
				answer += tmp;
				break;
			}
			tmp += w[o[j]];
		}
		//std::cout << tmp << std::endl;
	}
	std::cout << answer << std::endl;
	return 0;
}
