#include <cstdio>
#include <cstring>
#include <algorithm>

int x;
char s[1001];

int main() {
	scanf("%d of %s", &x, s);
	if (!strcmp(s, "week")) {
		int counter = 0;
		for (int i = 0; i < 366; i++)
			if ((i + 4) % 7 == (x - 1)) counter++;
		printf("%d\n", counter);
	} else {
		if (x == 31) printf("7\n");
		else if (x == 30) printf("%d\n", 7 + 4);
		else printf("12\n");
	}
	return 0;
}
