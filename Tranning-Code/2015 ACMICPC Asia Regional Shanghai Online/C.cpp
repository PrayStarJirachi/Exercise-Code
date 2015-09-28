#include <cstdio>

const int MAXN = 100001;

int T, len, last, size;
char s[MAXN];

void add(int x, int &last) {
	int newnode = ++size, lastnode = last; c[lastnode][x] = newnode;
	for (; c[lastnode][x]; lastnode = f[lastnode]);
	
}

int main() {
	freopen("C.in", "r", stdin);
	scanf("%d", &T);
	for (int cs = 1; cs <= T; cs++) {
		scanf("%s", s + 1);
		int len = strlen(s + 1);
		for (int i = 1; i <= len; i++) {
			add(s[i] - 'a', last);
		}
	}
	return 0;
}
