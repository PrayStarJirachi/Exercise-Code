
 #include <bits/stdc++.h>

int n, a[1001], b[1001];

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> n;
	for (int i = 1; i <= n; i++) std::cin >> a[i];
	for (int i = 1; i <= n; i++) std::cin >> b[i];
	int answer = 0;
	for (int i = 1; i <= n; i++) {
		int tmpA = 0, tmpB = 0;
		for (int j = i; j <= n; j++) {
			tmpA |= a[j];
			tmpB |= b[j];
			answer = std::max(answer, tmpA + tmpB);
		}
	}
	std::cout << answer << std::endl;;
	return 0;
}
