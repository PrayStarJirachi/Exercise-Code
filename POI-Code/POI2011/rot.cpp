#include <cstdio>
#include <algorithm>

#ifdef WIN32
	#define LL "%I64d"
#else
	#define LL "%lld"
#endif

const int MAXP = 7777777;

struct SegNode{
	SegNode *left, *right;
	int counter;
	SegNode() {
		left = right = NULL;
		counter = 0;
	}
}pool[MAXP];

int n, size;

SegNode *alloc() {
	SegNode *node;
	node = &pool[++size];
	node -> left = NULL;
	node -> right = NULL;
	node -> counter = 0;
	return node;
}

long long answer;
std::pair<long long, long long> counter;

SegNode *buildtree(int x, int l, int r) {
	SegNode *rt = alloc();
	rt -> counter++;
	if (l == r) return rt;
	if (x <= (l + r >> 1)) rt -> left = buildtree(x, l, l + r >> 1);
	else rt -> right = buildtree(x, (l + r >> 1) + 1, r);
	return rt;
}

SegNode *merge(SegNode *a, SegNode *b) {
	if (a == NULL) return b;
	if (b == NULL) return a;
	SegNode *now = alloc();
	now -> left = merge(a -> left, b -> left);
	now -> right = merge(a -> right, b -> right);
	now -> counter = a -> counter + b -> counter;
	if (a -> right != NULL && b -> left != NULL) {
		counter.first += 1ll * (a -> right -> counter) * (b -> left -> counter);
	}
	if (b -> right != NULL && a -> left != NULL) {
		counter.second += 1ll * (b -> right -> counter) * (a -> left -> counter);
	}
	return now;
}

SegNode *buildtree() {
	static int tmp;
	scanf("%d", &tmp);
	if (tmp != 0) {
		SegNode *rt = buildtree(tmp, 1, n);
		return rt;
	}
	else{
		SegNode *left = buildtree();
		SegNode *right = buildtree();
		counter.first = counter.second = 0;
		SegNode *rt = merge(left, right);
		answer += std::min(counter.first, counter.second);
		return rt;
	}
}

int main() {
	freopen("rot.in", "r", stdin);
	scanf("%d", &n);
	buildtree();
	printf(LL "\n", answer);
	return 0;
}
