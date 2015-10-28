#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

const int MAXN = 51;

class GreaterGame{
private:
	bool mark[MAXN * 2];
	std::vector<int> unknow;
public:
	double calc(std::vector <int> hand, std::vector <int> sothe) {
		int n = (int)hand.size();
		for (int i = 0; i < (int)hand.size(); i++) {
			mark[hand[i]] = true;
		}
		for (int i = 0; i < (int)sothe.size(); i++) {
			if (sothe[i] != -1) {
				mark[sothe[i]] = true;
			}
		}
		for (int i = 1; i <= 2 * n; i++) {
			if (!mark[i]) {
				unknow.push_back(i);
			}
		}
		std::sort(hand.begin(), hand.end());
		double answer = 0;
		std::sort(sothe.begin(), sothe.end());
		/*for (int i = 0; i < (int)hand.size(); i++)
			printf("%d%c", hand[i], " \n"[i + 1 == (int)hand.size()]);
		for (int i = 0; i < (int)sothe.size(); i++)
			printf("%d%c", sothe[i], " \n"[i + 1 == (int)sothe.size()]);*/
		for (int i = 0; i < (int)sothe.size(); i++) {
			if (sothe[i] == -1) continue;
			bool match = false;
			for (int j = 0; j < (int)hand.size(); j++) {
				if (hand[j] > sothe[i]) {
					std::swap(hand[j], hand[(int)hand.size() - 1]);
					hand.pop_back();
					std::sort(hand.begin(), hand.end());
					match = true;
					answer++;
					break;
				}
			}
			if (!match) {
				std::swap(hand[0], hand[(int)hand.size() - 1]);
				hand.pop_back();
				std::sort(hand.begin(), hand.end());
			}
		}
		/*for (int i = 0; i < (int)hand.size(); i++)
			printf("%d%c", hand[i], " \n"[i + 1 == (int)hand.size()]);*/
		for (int i = 0; i < (int)hand.size(); i++)
			for (int j = 0; j < (int)unknow.size(); j++)
				if (hand[i] > unknow[j]) {
					answer += 1.0 / unknow.size();
				}
		return answer;
	}
}T;

int n;
std::vector<int> sothe, hand;

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		hand.push_back(x);
	}
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		sothe.push_back(x);
	}
	printf("%.10f\n", T.calc(hand, sothe));
	return 0;
}
