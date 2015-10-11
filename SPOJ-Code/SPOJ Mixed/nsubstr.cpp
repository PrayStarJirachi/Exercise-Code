#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 800001;
const int MAXT = 800001;

int size, last, c[MAXT][26], f[MAXT], l[MAXT], r[MAXT], answer[MAXN];
char s[MAXN];

void add(int x, int &last) {
	int lastnode = last, newnode = ++size; l[newnode] = l[lastnode] + 1; r[newnode] = 1;
	for (; lastnode && !c[lastnode][x]; lastnode = f[lastnode]) c[lastnode][x] = newnode;
	if (!lastnode) f[newnode] = 1;
	else{
		int nownode = c[lastnode][x];
		if (l[lastnode] + 1 == l[nownode]) f[newnode] = nownode;
		else{
			int auxnode = ++size; l[auxnode] = l[lastnode] + 1;
			for (int i = 0; i < 26; i++) c[auxnode][i] = c[nownode][i];
			f[auxnode] = f[nownode]; f[nownode] = f[newnode] = auxnode;
			for (; lastnode && c[lastnode][x] == nownode; lastnode = f[lastnode]) c[lastnode][x] = auxnode;
		}
	}
	last = newnode;
}

void getright() {
	static int deg[MAXN], q[MAXN];
	for (int i = 1; i <= size; i++)
		if (f[i]) {
			deg[f[i]]++;
		}
	int left = 0, right = 0;
	for (int i = 1; i <= size; i++)
		if (!deg[i]) {
			q[++right] = i;
		}
	while (left < right) {
		left++;
		if (f[q[left]]) {
			r[f[q[left]]] += r[q[left]];
			if (!--deg[f[q[left]]]) {
				q[++right] = f[q[left]];
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%s", s + 1);
	int len = strlen(s + 1);
	last = size = 1;
	for (int i = 1; i <= len; i++) {
		add(s[i] - 'a', last);
	}
	getright();
	for (int i = 2; i <= size; i++) {
		answer[l[i]] = std::max(answer[l[i]], r[i]);
	}
	for (int i = len; i >= 1; i--)
		answer[i] = std::max(answer[i], answer[i + 1]);
	for (int i = 1; i <= len; i++) {
		printf("%d\n", answer[i]);
	}
	return 0;
}
