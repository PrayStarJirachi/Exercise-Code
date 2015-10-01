#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXN = 3000001;
const int Maxdata = 3000000;

int g, p[MAXN];
long long phi[MAXN];
bool vis[MAXN];

int main() {
	phi[1] = 1;
	for (int i = 2; i <= Maxdata; i++) {
		if (!vis[i]) phi[p[++g] = i] = i - 1;
		for (int j = 1; i * p[j] <= Maxdata && j <= g; j++) {
			vis[i * p[j]] = true;
			if (i % p[j] == 0) {
				phi[i * p[j]] = phi[i] * p[j];
				break;
			}
			else phi[i * p[j]] = phi[i] * phi[p[j]];
		}
	}
	for (int i = 2; i <= Maxdata; i++)
		phi[i] += phi[i - 1];
	int l, r;
	while (scanf("%d%d", &l, &r) == 2) {
		printf(LL "\n", phi[r] - phi[l - 1]);
	}
	return 0;
}
