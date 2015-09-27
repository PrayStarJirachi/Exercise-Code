#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

std::vector<std::pair<int, int> > vec;

int main() {
	srand(time(NULL));
	freopen("I.in", "w", stdout);
	int T = 1;
	printf("%d\n", T);
	for (int cs = 1; cs <= T; cs++) {
		int n = 30, m = 100, q = 100;
		printf("%d %d %d\n", n, m, q);
		for (int i = 2; i <= n; i++) printf("%d %d\n", rand() % (i - 1) + 1, i);
		vec.clear();
		for (int i = n; i <= m; i++) {
			int x = rand() % n + 1;
			int y = rand() % n + 1;
			vec.push_back(std::make_pair(x, y));
		}
		std::random_shuffle(vec.begin(), vec.end());
		for (int i = 1; i <= q; i++) {
			int op = rand() % 2 + 1;
			if (op == 1 && !(int)vec.size()) op = 2;
			if (op == 1) {
				std::pair<int, int> now = vec[(int)vec.size() - 1];
				vec.pop_back();
				printf("%d %d %d\n", op, now.first, now.second);
			}
			else{
				int x = rand() % n + 1;
				int y = rand() % n + 1;
				printf("%d %d %d\n", op, x, y);
			}
		}
	}
	return 0;
}
