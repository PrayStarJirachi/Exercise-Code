#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int x1, y1, x2, y2, N, M, n;
int x[105][3], y[105][3];
int tmpx[505], tmpy[505];
int num[505][505];
bool con[120][120][4][4];
int pre[4], suc[4], opo[4];

struct point {
	int x, y, face;
} que[500005];

int d[120][120][4];
bool vis[120][120][4];

int ava(int x, int y) {
	if (x < 1 || x > N || y < 1 || y > M) return 0;
	return 1;
}

int abs(int x) {
	if (x < 0) return -x;
	return x;
}

void BFS() {
	int head = 0;
	int tail = 0;
	for (int i = 1; i <= N; i ++)
		for (int j = 1; j <= M; j ++)
			for (int k = 0; k < 4; k ++)
				d[i][j][k] = 1 << 29;
	for (int i = 0; i < 4; i ++) {
		++tail;
		que[tail].x = x1;
		que[tail].y = y1;
		que[tail].face = i;
		d[x1][y1][i] = 0;
	}
	while (head != tail) {
		head = head % 500000 + 1;
		point cur = que[head];
		vis[cur.x][cur.y][cur.face] = 0;
		for (int k = 0; k < 4; k ++) 
			if (con[cur.x][cur.y][cur.face][k]) {
				int calc = 1;
				if (abs(cur.face - k) == 2) calc = 0;
//				printf("%d\n", calc);
				int nx = cur.x + dx[k];
				int ny = cur.y + dy[k];
				if (ava(nx, ny)) {
					if (d[nx][ny][opo[k]] > d[cur.x][cur.y][cur.face] + calc) {
						d[nx][ny][opo[k]] = d[cur.x][cur.y][cur.face] + calc;
						if (!vis[nx][ny][opo[k]]) {
							vis[nx][ny][opo[k]] = 1;
							if (calc == 0) {
								que[head].x = nx;
								que[head].y = ny;
								que[head].face = opo[k];
								head --;
								if (head == 0) head = 500000;
							} else {
								tail = tail % 500000 + 1;
								que[tail].x = nx;
								que[tail].y = ny;
								que[tail].face = opo[k];
							}
						}
					}
				}
			}
	}
	int ans = 1 << 29;
//	printf("%d %d %d %d\n", x1, y1, x2, y2);
//	cout << tail << endl;
	for (int k = 0; k < 4; k ++) {
		ans = min(ans, d[x2][y2][k]);
	}
	if (ans == (1 << 29)) puts("-1");
		else printf("%d\n", ans);
}

int main() {
	for (int i = 0; i < 4; i ++) {
		pre[i] = i - 1;
		suc[i] = i + 1;
	}
	pre[0] = 3;
	suc[3] = 0;

	opo[0] = 2;
	opo[1] = 3;
	opo[2] = 0;
	opo[3] = 1;

	while (scanf("%d%d%d%d", &x1, &y1, &x2, &y2) == 4) {
		if (x1 == 0 && x1 == x2 && x2 == y1 && y1 == y2) break;
		int sum1 = 4;
		int sum2 = 4;
		tmpx[1] = tmpy[1] = -(1e9);
		tmpx[2] = tmpy[2] = 1e9;
		tmpx[3] = x1;
		tmpx[4] = x2;
		tmpy[3] = y1;
		tmpy[4] = y2;
		scanf("%d", &n);
		for (int i = 1; i <= n; i ++) {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			x[i][0] = min(a, c);
			x[i][1] = max(a, c);
			y[i][0] = min(b, d); 
			y[i][1] = max(b, d);
			tmpx[++sum1] = x[i][0];
			tmpx[++sum1] = x[i][1];
			tmpy[++sum2] = y[i][0];
			tmpy[++sum2] = y[i][1];
		}
		sort(tmpx + 1, tmpx + sum1 + 1);
		sort(tmpy + 1, tmpy + sum2 + 1);
		N = 1;
		M = 1;
		for (int i = 2; i <= sum1; i ++) 
			if (tmpx[i] != tmpx[i - 1]) {
				tmpx[++N] = tmpx[i];
			}
		for (int i = 2; i <= sum2; i ++) 
			if (tmpy[i] != tmpy[i - 1]) {
				tmpy[++M] = tmpy[i];
			}
		/*
		for (int i = 1; i <= N; i ++) printf("%d ", tmpx[i]);
		puts("");
		for (int i = 1; i <= M; i ++) printf("%d ", tmpy[i]);
		puts("");
		*/
		int xmin, xmax, ymin, ymax;
		bool flag1 = 0;
		bool flag2 = 0;
		for (int i = 1; i <= N; i ++)
			for (int j = 1; j <= M; j ++) {
				if (tmpx[i] == x1 && tmpy[j] == y1 && (!flag1)) {
					x1 = i;
					y1 = j;
					flag1 = 1;
				}
				if (tmpx[i] == x2 && tmpy[j] == y2 && (!flag2)) {
					x2 = i;
					y2 = j;
					flag2 = 1;
				}
				for (int p = 0; p < 4; p ++)
					for (int q = 0; q < 4; q ++)
						con[i][j][p][q] = 0;
				for (int p = 0; p < 4; p ++) {
					con[i][j][p][pre[p]] = 1;
					con[i][j][p][suc[p]] = 1;
				}
				for (int k = 1; k <= n; k ++) {
					xmin = x[k][0];
					xmax = x[k][1];
					ymin = y[k][0];
					ymax = y[k][1];
					if (tmpx[i] > xmin && tmpx[i] < xmax && tmpy[j] > ymin && tmpy[j] < ymax) {
						for (int p = 0; p < 4; p ++) {
							con[i][j][p][suc[p]] = con[i][j][p][pre[p]] = 0;
						}
						break;
					} else {
						int num = -1;
						if (tmpx[i] == xmin && tmpy[j] == ymin) num = 0;
						if (tmpx[i] == xmax && tmpy[j] == ymin) num = 1;
						if (tmpx[i] == xmax && tmpy[j] == ymax) num = 2;
						if (tmpx[i] == xmin && tmpy[j] == ymax) num = 3;
						if (num != -1) {
							con[i][j][num][suc[num]] = 0;
							con[i][j][suc[num]][num] = 0;
						} else {
							if (tmpx[i] == xmin && tmpy[j] > ymin && tmpy[j] < ymax) num = 0;
							if (tmpx[i] == xmax && tmpy[j] > ymin && tmpy[j] < ymax) num = 2;
							if (tmpy[j] == ymin && tmpx[i] > xmin && tmpx[i] < xmax) num = 1;
							if (tmpy[j] == ymax && tmpx[i] > xmin && tmpx[i] < xmax) num = 3;
							if (num != -1) {
								con[i][j][num][pre[num]] = 0;
								con[i][j][num][suc[num]] = 0;
								con[i][j][pre[num]][num] = 0;
								con[i][j][suc[num]][num] = 0;
							}
						}
//						printf("%d %d %d\n", tmpx[i], tmpy[j], num);
					}
				}
				for (int k = 0; k < 4; k ++)
					for (int p = 0; p < 4; p ++)
						for (int q = 0; q < 4; q ++) 
							if (con[i][j][p][k] && con[i][j][k][q])
								con[i][j][p][q] = 1;
			}
		BFS();		
	}
	return 0;
}
