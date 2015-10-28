#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

const int MAXN = 300001;
const int minCapacity = 9001;
const int maxCapacity = 30000001;

class Over9000Rocks{
private:
	struct Node{
		int l, r, d;
	}t[MAXN * 6];
	int rt, size, flag[MAXN * 6];
	void alloc(int &rt) {
		if (!rt) {
			rt = ++size;
			t[rt].l = t[rt].r = t[rt].d = 0;
			flag[rt] = 0;
		}
	}
	void makesame(int rt, int l, int r) {
		flag[rt] = true;
		t[rt].d = r - l + 1;
	}
	void pushdown(int rt, int l, int r) {
		if (flag[rt]) {
			alloc(t[rt].l);
			alloc(t[rt].r);
			makesame(t[rt].l, l, l + r >> 1);
			makesame(t[rt].r, (l + r >> 1) + 1, r);
			flag[rt] = false;
		}
	}
	void cover(int &rt, int l, int r, int x, int y) {
		if (r < x || l > y) return;
		alloc(rt);
		if (x <= l && r <= y) {
			makesame(rt, l, r);
			return;
		}
		pushdown(rt, l, r);
		cover(t[rt].l, l, l + r >> 1, x, y);
		cover(t[rt].r, (l + r >> 1) + 1, r, x, y);
		t[rt].d = t[t[rt].l].d + t[t[rt].r].d;
	}
public:
	int countPossibilities(std::vector<int> lower, std::vector<int> upper) {
		int n = lower.size();
		for (int i = 0; i < (1 << n); i++) {
			int nowLowerBound = 0;
			int nowUpperBound = 0;
			for (int j = 0; j < n; j++) {
				if (i & (1 << j)) {
					nowLowerBound += lower[j];
					nowUpperBound += upper[j];
				}
			}
			nowLowerBound = std::max(nowLowerBound, 9001);
			if (nowUpperBound < nowLowerBound) continue;
			cover(rt, minCapacity, maxCapacity, nowLowerBound, nowUpperBound);
		}
		return t[rt].d;
	}
};
