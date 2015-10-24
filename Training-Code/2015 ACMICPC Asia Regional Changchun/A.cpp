#include <cstdio>
#include <algorithm>

const int MAXN = 11;
const int nValue = 10;
const int VALUE[] = {1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000};

int T, total, l[MAXN];

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &total);
		int answer = 0;
		for (int i = 0; i < nValue; i++) {
			scanf("%d", l + i);
			total = total - l[i] * VALUE[i];
			answer += l[i];
		}
		if (total > 0) {
			puts("-1");
			continue;
		}
		total = -total;
		for (int i = nValue - 1; i >= 0; i--) {
			int tmp = total / VALUE[i];
			tmp = std::min(tmp, l[i]);
			answer -= tmp;
			total -= tmp * VALUE[i];
		}
		if (total != 0) puts("-1");
		else printf("%d\n", answer);
	}
	return 0;
}
