#include <cstdio>
#include <iostream>
#include <algorithm>

const int MAXH = 20;
const int Maxlog = 18;
const int MAXS = 18 * 9;
const int MAXK = 1001;

int k, lB[MAXH], rB[MAXH];
std::pair<long long, int> dp[MAXH][MAXS][MAXK][2][2];
bool v[MAXH][MAXS][MAXK][2][2];
long long l, r;

std::pair<long long, int> dfs(int depth, int digitSum, int prevSum, int leftBound, int rightBound) {
	if (v[depth][digitSum][prevSum][leftBound][rightBound]) {
		return dp[depth][digitSum][prevSum][leftBound][rightBound];
	}
	v[depth][digitSum][prevSum][leftBound][rightBound] = true;
	std::pair<long long, int> &now = dp[depth][digitSum][prevSum][leftBound][rightBound];
	if (depth == 0) {
		if (digitSum + prevSum >= k) return now = std::make_pair(1, 0);
		else return now = std::make_pair(0, digitSum + prevSum);
	}
	int leftLimit = leftBound ? lB[depth] : 0;
	int rightLimit = rightBound ? rB[depth] : 9;
	now = std::make_pair(0, prevSum);
	for (int nextDigit = leftLimit; nextDigit <= rightLimit; nextDigit++) {
		std::pair<long long, int> tmp;
		int nextLeftBound = leftBound && (nextDigit == leftLimit);
		int nextRightBound = rightBound && (nextDigit == rightLimit);
		tmp = dfs(depth - 1, digitSum + nextDigit, now.second, nextLeftBound, nextRightBound);
		now = std::make_pair(now.first + tmp.first, tmp.second);
	}
	return now;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> l >> r >> k;
	for (int i = 1; i <= Maxlog; i++) {
		lB[i] = l % 10; l /= 10;
		rB[i] = r % 10; r /= 10;
	}
	std::cout << dfs(Maxlog, 0, 0, 1, 1).first << std::endl;
	return 0;
}
