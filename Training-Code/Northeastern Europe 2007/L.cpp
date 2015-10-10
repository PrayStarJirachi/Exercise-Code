#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int pow1 = 96821;
const int pow2 = 34919;
const int mod1 = 998244353;
const int mod2 = 950009857;
const int MAXT = 200001;

int n, size, answer, c[MAXT][26];
char s[MAXT], d[MAXT];
bool v[MAXT], e[MAXT];
std::vector<std::pair<int, int> > vector;
std::pair<int, int> hash[MAXT];

int alloc() {
	size++;
	std::fill(c[size], c[size] + 26, 0);
	d[size] = ' ';
	v[size] = false;
	e[size] = false;
	return size;
}

void insert(char *s) {
	int p = 1, len = strlen(s + 1);
	for (int i = 1; i <= len; i++) {
		if (c[p][s[i] - 'a']) p = c[p][s[i] - 'a'];
		else{
			int newnode = alloc();
			c[p][s[i] - 'a'] = newnode;
			d[newnode] = s[i];
			p = newnode;
		}
	}
	e[p] = true;
}

int bfs(int x) {
	static int q[MAXT];
	int left = 0, right = 0;
	q[++right] = x;
	while (left < right) {
		left++;
		for (int i = 0; i < 26; i++)
			if (c[q[left]][i]) {
				q[++right] = c[q[left]][i];
			}
	}
	vector.clear();
	for (int i = right; i >= 1; i--) {
		hash[q[i]] = std::make_pair(13, 19);
		for (int j = 0; j < 26; j++) {
			hash[q[i]].first = ((long long)hash[q[i]].first * pow1 + hash[c[q[i]][j]].first) % mod1;
			hash[q[i]].second = ((long long)hash[q[i]].second * pow2 + hash[c[q[i]][j]].second) % mod2;
		}
		hash[q[i]].first = ((long long)hash[q[i]].first * pow1 + 13 + e[q[i]]) % mod1;
		hash[q[i]].second = ((long long)hash[q[i]].second * pow2 + 19 + e[q[i]]) % mod2;
		vector.push_back(hash[q[i]]);
	}
	std::sort(vector.begin(), vector.end());
	vector.erase(unique(vector.begin(), vector.end()), vector.end());
	return vector.size();
}

int main() {
	freopen("input.txt", "r", stdin);
	while (scanf("%d", &n) == 1) {
		size = 0;
		alloc();
		for (int i = 1; i <= n; i++) {
			scanf("%s", s + 1);
			insert(s);
		}
		printf("%d\n", bfs(1));
	}
	return 0;
}
