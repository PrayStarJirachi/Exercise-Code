#include <cmath>
#include <cstdio>
#include <algorithm>

const int MAXN = 111;
const double PI = acos(-1.0);//3.1415926535897932384626;
const double EPS = 1e-8;
const int INF = ~0u >> 2;

int T, n;
double a[MAXN];

int dcmp(const double &x) {
	return (fabs(x) < EPS) ? 0 : (x > 0 ? 1 : -1);
}

int check(const double &d) {
	double sumangle = 0;
	for (int i = 0; i < n; i++) {
		double alpha = (a[i] * a[i] + a[(i + 1) % n] * a[(i + 1) % n] - d * d) / 2.0 / a[i] / a[(i + 1) % n];
		sumangle += acos(alpha);
	}
	return dcmp(sumangle - 2 * PI);
}

bool check2(double mid) {
	for (int i = 0; i < n; ++i){
		if (dcmp(mid - a[i]- a[(i + 1) % n]) >= 0 || 
		    dcmp(-mid + a[i] - a[(i + 1) % n]) >= 0 || 
		    dcmp(-mid - a[i] + a[(i + 1) % n])>=0) {
			return false;
		}
	}
	return true;
}

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%d", &n);
		std::pair<double, double> ret = std::make_pair(-INF, INF);
		for (int i = 0; i < n; i++) scanf("%lf", a + i);
		for (int i = 0; i < n; i++) {
			ret.first = std::max(ret.first, fabs(a[i] - a[(i + 1) % n]));
			ret.second = std::min(ret.second, a[i] + a[(i + 1) % n]);
		}
		if (dcmp(ret.first - ret.second) > 0) {
			printf("Case %d: impossible\n", cs);
			continue;
		}
		double left = ret.first, right = ret.second;
		for (int t = 1; t <= 100; t++) {
			double mid = (left + right) / 2.0;
			if (check(mid) <= 0) left = mid;
			else right = mid;
		}
		if (!check2(left)) printf("Case %d: impossible\n", cs);
		else printf("Case %d: %.3f\n", cs, left);
	}
	return 0;
}
