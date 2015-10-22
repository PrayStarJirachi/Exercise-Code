#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

const int MAXT = 400001;
const int MAXN = 200001;
const int MAXM = 800001;
const int MAXL = 800001;
const int MAXD = 10000001;

struct StackNode{
	int node, cur;
}z[MAXT];

struct TNode{
	int l, r;
	long long d;
}tree[MAXD];

struct Edge{
	int node, next;
}e[MAXM];

int n, m, size, cnt, last, t, tot, h[MAXT], pos[MAXT], c[MAXT][26], p[MAXT];
int rt[MAXN], f[MAXT], l[MAXT], oL[MAXT], oR[MAXT];
char s[MAXL];

void addedge(int x, int y) {
	t++; e[t] = (Edge){y, h[x]}; h[x] = t;
}

void add(int x, int &last) {
	int lastnode = last;
	if (c[lastnode][x]) {
		int nownode = c[lastnode][x];
		if (l[nownode] == l[lastnode] + 1) last = nownode;
		else{
			int auxnode = ++size; l[auxnode] = l[lastnode] + 1;
			for (int i = 0; i < 26; i++) c[auxnode][i] = c[nownode][i];
			f[auxnode] = f[nownode]; f[nownode] = auxnode;
			for (; lastnode && c[lastnode][x] == nownode; lastnode = f[lastnode]) {
				c[lastnode][x] = auxnode;
			}
			last = auxnode;
		}
	}
	else{
		int newnode = ++size; l[newnode] = l[lastnode] + 1;
		for (; lastnode && !c[lastnode][x]; lastnode = f[lastnode]) c[lastnode][x] = newnode;
		if (!lastnode) f[newnode] = 1;
		else{
			int nownode = c[lastnode][x];
			if (l[nownode] == l[lastnode] + 1) f[newnode] = nownode;
			else{
				int auxnode = ++size; l[auxnode] = l[lastnode] + 1;
				for (int i = 0; i < 26; i++) c[auxnode][i] = c[nownode][i];
				f[auxnode] = f[nownode]; f[nownode] = f[newnode] = auxnode;
				for (; lastnode && c[lastnode][x] == nownode; lastnode = f[lastnode]) {
					c[lastnode][x] = auxnode;
				}
			}
		}
		last = newnode;
	}
}

void dfs(int x) {
	int top = 0;
	z[++top] = (StackNode){x, h[x]};
	while (top != 0) {
		StackNode &now = z[top];
		if (now.cur == h[now.node]) oL[now.node] = ++tot;
		if (!now.cur) {
			oR[now.node] = tot;
			top--;
			continue;
		}
		for (; now.cur; now.cur = e[now.cur].next) {
			z[++top] = (StackNode){e[now.cur].node, h[e[now.cur].node]};
			now.cur = e[now.cur].next;
			break;
		}
	}
}

void insert(int rt, int &newrt, int l, int r, int x, int d) {
	tree[newrt = ++cnt] = tree[rt];
	tree[newrt].d += d;
	if (l == r) return;
	if (x <= (l + r >> 1)) insert(tree[rt].l, tree[newrt].l, l, l + r >> 1, x, d);
	else insert(tree[rt].r, tree[newrt].r, (l + r >> 1) + 1, r, x, d);
}

long long query(int xrt, int yrt, int l, int r, int x, int y) {
	if (r < x || l > y) return 0;
	if (x <= l && r <= y) return tree[yrt].d - tree[xrt].d;
	long long left = query(tree[xrt].l, tree[yrt].l, l, l + r >> 1, x, y);
	long long right = query(tree[xrt].r, tree[yrt].r, (l + r >> 1) + 1, r, x, y);
	return left + right;
}

int main() {
/*int used = sizeof(tree) + sizeof(z) + sizeof(e) + sizeof(h) + sizeof(pos) + sizeof(c) + sizeof(p) + 
sizeof(rt) + sizeof(f) + sizeof(l) + sizeof(oL) + sizeof(oR) + sizeof(s);
printf("%d\n", used / 1048576);*/
	freopen("E.in", "r", stdin);
	scanf("%d%d", &n, &m);
	last = size = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%s", s + p[i - 1]);
		int len = strlen(s + p[i - 1]);
		p[i] = p[i - 1] + len;
		last = 1;
		for (int j = p[i - 1]; j < p[i]; j++) {
			add(s[j] - 'a', last);
		}
		pos[i] = last;
	}
	for (int i = 1; i <= size; i++) {
		if (f[i]) addedge(f[i], i);
	}
	dfs(1);
	for (int i = 1; i <= n; i++) {
		rt[i] = rt[i - 1];
		int now = 1;
		insert(rt[i], rt[i], 1, size, oL[now], 1);
		for (int j = p[i - 1]; j < p[i]; j++) {
			now = c[now][s[j] - 'a'];
			insert(rt[i], rt[i], 1, size, oL[now], 1);
		}
	}
	//printf("%d %d\n", size, cnt);
	for (int i = 1; i <= m; i++) {
		int x, y, d;
		scanf("%d%d%d", &x, &y, &d);
		long long answer = query(rt[x - 1], rt[y], 1, size, oL[pos[d]], oR[pos[d]]);
		printf("%lld\n", answer);
	}
	return 0;
}
