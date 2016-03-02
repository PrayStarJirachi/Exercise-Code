#include <cstdio>
#include <algorithm>

const int MAXN = 400001;

int n, t, q, M, p[MAXN], l[MAXN];

struct Box{
	int now, total, id;
	Box() {}
	Box(int now, int total, int id) : now(now), total(total), id(id) {}
	double value()const {
		return 1.0 * now / total * p[id];
	}
	Box add()const {
		if (now == l[id]) return *this;
		return Box(now + 1, total + 1, id);
	}
	Box red()const {
		if (now == 0) return *this;
		return Box(now - 1, total - 1, id);
	}
}b[MAXN], tree[MAXN * 4][2];

struct CmpMax{
	Box operator ()(const Box &a, const Box &b)const {
		double valueA = a.add().value() - a.value();
		double valueB = b.add().value() - b.value();
		return valueA > valueB ? a : b;
	}
}max;

struct CmpMin{
	Box operator ()(const Box &a, const Box &b)const {
		if (a.now == 0) return b;
		if (b.now == 0) return a;
		double valueA = a.value() - a.red().value();
		double valueB = b.value() - b.red().value();
		return valueA < valueB ? a : b;
	}
}min;

std::pair<Box, Box> query(int l, int r) {
	std::pair<Box, Box> ret;
	bool flag = false;
	for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if (l & 1 ^ 1) {
			if (!flag) {
				ret = std::make_pair(tree[l ^ 1][0], tree[l ^ 1][1]);
				flag = true;
			} else {
				ret.first = min(ret.first, tree[l ^ 1][0]);
				ret.second = max(ret.second, tree[l ^ 1][1]);
			}
		}
		if (r & 1) {
			if (!flag) {
				ret = std::make_pair(tree[r ^ 1][0], tree[r ^ 1][1]);
				flag = true;
			} else {
				ret.first = min(ret.first, tree[r ^ 1][0]);
				ret.second = max(ret.second, tree[r ^ 1][1]);
			}
		}
	}
	return ret;
}

void modify(int x, const Box &data) {
	for (x += M, tree[x][0] = tree[x][1] = data, x >>= 1; x; x >>= 1) {
		tree[x][0] = min(tree[x << 1][0], tree[x << 1 ^ 1][0]);
		tree[x][1] = max(tree[x << 1][1], tree[x << 1 ^ 1][1]);
	}
}

int main() {
	freopen("G.in", "r", stdin);
	scanf("%d%d%d", &n, &t, &q);
	for (int i = 1; i <= n; i++) scanf("%d", p + i);
	for (int i = 1; i <= n; i++) scanf("%d", l + i);
	for (M = 1; M <= n + 1; M <<= 1);
	for (int i = 1; i <= n; i++) {
		b[i] = Box(0, l[i], i);
		modify(i, b[i]);
	}
	double answer = 0;
	for (int cs = 1; cs <= q; cs++) {
		int op, x;
		scanf("%d%d", &op, &x);
		if (op == 1) {
			answer -= b[x].value();
			l[x]++;
			b[x].total++;
			if (b[x].now > 0) {
				b[x].now--;
				b[x].total--;
				t++;
			}
			answer += b[x].value();
			modify(x, b[x]);
		} else {
			answer -= b[x].value();
			l[x]--;
			b[x].total--;
			if (b[x].now > l[x]) {
				b[x].now--;
				b[x].total--;
				t++;
			}
			answer += b[x].value();
			modify(x, b[x]);
		}
		std::pair<Box, Box> top;
		if (x == 1) top = query(2, n);
		else if (x == n) top = query(1, n - 1);
		else{
			std::pair<Box, Box> a = query(1, x - 1), b = query(x + 1, n);
			top.first = min(a.first, b.first);
			top.second = max(a.second, b.second);
		}
		if (b[x].now < l[x] && top.first.now > 0) {
			if (b[x].add().value() - b[x].value() > top.first.value() - top.first.red().value()) {
				answer -= b[x].value();
				b[x].now++;
				b[x].total++;
				answer += b[x].value();
				modify(x, b[x]);
				
				answer -= b[top.first.id].value();
				b[top.first.id].now--;
				b[top.first.id].total--;
				answer += b[top.first.id].value();
				modify(top.first.id, b[top.first.id]);
			}
		}
		while (t > 0) {
			std::pair<Box, Box> top = query(1, n);
			if (top.second.now == l[top.second.id]) break;
			t--;
			answer -= b[top.second.id].value();
			b[top.second.id].now++;
			b[top.second.id].total++;
			answer += b[top.second.id].value();
			modify(top.second.id, b[top.second.id]);
		}
		/*for (int j = 1; j<= n; j++) {
			std::cout << b[j].now << " ";
		}
		std::cout << std::endl;*/
		printf("%.8f\n", answer);
	}
	return 0;
}
