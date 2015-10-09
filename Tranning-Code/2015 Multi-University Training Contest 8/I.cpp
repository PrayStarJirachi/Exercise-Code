#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define DB "%.6f"

const int MAXD = 4;
const int MAXN = 250001;

struct Matrix{
	double a[MAXD][MAXD];
	Matrix operator *(const Matrix &rhs) {
		Matrix ret;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) {
				ret.a[i][j] = 0;
				for (int k = 0; k < 4; k++)
					ret.a[i][j] += a[i][k] * rhs.a[k][j];
			}
		return ret;
	}
}I;

Matrix getTrans(const double &a, const double &b, const double &c) {
	Matrix ret;
	ret.a[0][0] = 1; ret.a[0][1] = 0; ret.a[0][2] = 0; ret.a[0][3] = 0;
	ret.a[1][0] = 0; ret.a[1][1] = 1; ret.a[1][2] = 0; ret.a[1][3] = 0;
	ret.a[2][0] = 0; ret.a[2][1] = 0; ret.a[2][2] = 1; ret.a[2][3] = 0;
	ret.a[3][0] = a; ret.a[3][1] = b; ret.a[3][2] = c; ret.a[3][3] = 1;
	return ret;
}

Matrix getScale(const double &a, const double &b, const double &c, const double &k) {
	Matrix ret;
	ret.a[0][0] = k; ret.a[0][1] = 0; ret.a[0][2] = 0; ret.a[0][3] = 0;
	ret.a[1][0] = 0; ret.a[1][1] = k; ret.a[1][2] = 0; ret.a[1][3] = 0;
	ret.a[2][0] = 0; ret.a[2][1] = 0; ret.a[2][2] = k; ret.a[2][3] = 0;
	ret.a[3][0] = 0; ret.a[3][1] = 0; ret.a[3][2] = 0; ret.a[3][3] = 1;
	return getTrans(-a, -b, -c) * ret * getTrans(a, b, c);
}

Matrix getRotate(const double &a, const double &b, const double &c, const double &theta) {
	Matrix ret;
	ret.a[0][0] = a * a * (1 - cos(theta)) + cos(theta);
	ret.a[0][1] = a * b * (1 - cos(theta)) + c * sin(theta);
	ret.a[0][2] = a * c * (1 - cos(theta)) - b * sin(theta);
	ret.a[0][3] = 0;
	
	ret.a[1][0] = b * a * (1 - cos(theta)) - c * sin(theta);
	ret.a[1][1] = b * b * (1 - cos(theta)) + cos(theta);
	ret.a[1][2] = b * c * (1 - cos(theta)) + a * sin(theta);
	ret.a[1][3] = 0;
	
	ret.a[2][0] = c * a * (1 - cos(theta)) + b * sin(theta);
	ret.a[2][1] = c * b * (1 - cos(theta)) - a * sin(theta);
	ret.a[2][2] = c * c * (1 - cos(theta)) + cos(theta);
	ret.a[2][3] = 0;
	
	ret.a[3][0] = 0;
	ret.a[3][1] = 0;
	ret.a[3][2] = 0;
	ret.a[3][3] = 1;
	return ret;
}

struct Point{
	double x, y, z;
	Point() {}
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	void read() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	void print() {
		printf(DB " " DB " " DB "\n", x, y, z);
	}
}p[MAXN];

double dist(const Point &a, const Point &b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

Matrix getRotate(const double &ax, const double &ay, const double &az, const double &bx, const double &by, const double &bz, const double &theta) {
	double l = dist(Point(0, 0, 0), Point(bx, by, bz));
	Matrix ret = getTrans(-ax, -ay, -az);
	ret = ret * getRotate(bx / l, by / l, bz / l, theta);
	ret = ret * getTrans(ax, ay, az);
	return ret;
}

Point operator *(const Point &a, const Matrix &b) {
	Point ret;
	ret.x = a.x * b.a[0][0] + a.y * b.a[1][0] + a.z * b.a[2][0] + b.a[3][0];
	ret.y = a.x * b.a[0][1] + a.y * b.a[1][1] + a.z * b.a[2][1] + b.a[3][1];
	ret.z = a.x * b.a[0][2] + a.y * b.a[1][2] + a.z * b.a[2][2] + b.a[3][2];
	return ret;
}

struct Node{
	Point l, r;
	double len;
	Node() {}
	Node(Point a, Point b) : l(a), r(b) {
		len = dist(a, b);
	}
	Node operator +(const Node &rhs)const {
		Node ret;
		ret.len = len + dist(r, rhs.l) + rhs.len;
		ret.l = l;
		ret.r = rhs.r;
		return ret;
	}
}tree[MAXN * 6];

int n, m, cs;
bool v[MAXN * 6];
double fK[MAXN * 6];
Matrix fM[MAXN * 6];

void multiply(int n, const double &k, const Matrix &d) {
	v[n] = true;
	fK[n] = fK[n] * k;
	fM[n] = fM[n] * d;
	tree[n].l = tree[n].l * d;
	tree[n].r = tree[n].r * d;
	tree[n].len = tree[n].len * k;
}

void pushdown(int n) {
	if (v[n]) {
		multiply(n << 1, fK[n], fM[n]);
		multiply(n << 1 ^ 1, fK[n], fM[n]);
		fK[n] = 1.0;
		fM[n] = I;
		v[n] = false;
	}
}

void modify(int n, int l, int r, int x, int y, const double &k, const Matrix &d) {
	if (r < x || l > y) return;
	if (x <= l && r <= y) {
		multiply(n, k, d);
		return;
	}
	pushdown(n);
	modify(n << 1, l, l + r >> 1, x, y, k, d);
	modify(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y, k, d);
	tree[n] = tree[n << 1] + tree[n << 1 ^ 1];
}

Node query(int n, int l, int r, int x, int y) {
	if (x <= l && r <= y) return tree[n];
	pushdown(n);
	if ((l + r >> 1) < x) return query(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
	else if ((l + r >> 1) + 1 > y) return query(n << 1, l, l + r >> 1, x, y);
	else{
		Node left = query(n << 1, l, l + r >> 1, x, y);
		Node right = query(n << 1 ^ 1, (l + r >> 1) + 1, r, x, y);
		return left + right;
	}
}

Node query(int n, int l, int r, int x) {
	if (l == r) return tree[n];
	pushdown(n);
	if (x <= (l + r >> 1)) return query(n << 1, l, l + r >> 1, x);
	else return query(n << 1 ^ 1, (l + r >> 1) + 1, r, x);
}

void buildtree(int n, int l, int r) {
	fK[n] = 1.0;
	fM[n] = I;
	if (l == r) {
		tree[n] = Node(p[l], p[r]);
		return;
	}
	buildtree(n << 1, l, l + r >> 1);
	buildtree(n << 1 ^ 1, (l + r >> 1) + 1, r);
	tree[n] = tree[n << 1] + tree[n << 1 ^ 1];
}

int main() {
	freopen("I.in", "r", stdin);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			I.a[i][j] = (i == j);
	while (scanf("%d%d", &n, &m) == 2) {
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= n; i++) p[i].read();
		buildtree(1, 1, n);
		printf("Case #%d:\n", ++cs);
		for (int i = 1; i <= m; i++) {
			char op[20];
			int l, r, x;
			double ax, ay, az, bx, by, bz, k, theta;
			scanf("%s", op);
			if (!strcmp(op, "Translation")) {
				scanf("%d%d%lf%lf%lf", &l, &r, &ax, &ay, &az);
				modify(1, 1, n, l, r, 1.0, getTrans(ax, ay, az));
			}
			else if (!strcmp(op, "Scaling")) {
				scanf("%d%d%lf%lf%lf%lf", &l, &r, &ax, &ay, &az, &k);
				modify(1, 1, n, l, r, k, getScale(ax, ay, az, k));
			}
			else if (!strcmp(op, "Rotation")) {
				scanf("%d%d%lf%lf%lf%lf%lf%lf%lf", &l, &r, &ax, &ay, &az, &bx, &by, &bz, &theta);
				modify(1, 1, n, l, r, 1.0, getRotate(ax, ay, az, bx, by, bz, theta));
			}
			else if (!strcmp(op, "Coordinates")) {
				scanf("%d", &x);
				Node ret = query(1, 1, n, x);
				ret.l.print();
			}
			else if (!strcmp(op, "Length")) {
				scanf("%d%d", &l, &r);
				Node ret = query(1, 1, n, l, r);
				printf(DB "\n", ret.len);
			}
		}
	}
	return 0;
}
