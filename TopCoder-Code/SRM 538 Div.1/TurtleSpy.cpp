#include <cstdio>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>

const int MAXANGLE = 360;
const double pi = 3.1415926535897932384626;

class TurtleSpy{
public:
	bool dp[MAXANGLE], tmp[MAXANGLE];
	std::string getCommand(const std::string &x) {
		return x.substr(0, x.find(" "));
	}
	int getValue(const std::string &x) {
		return atoi(x.substr(x.find(" ") + 1, x.size() - x.find(" ")).c_str());
	}
	double maxDistance(std::vector<std::string> c) {
		dp[0] = true;
		int forwardStep = 0;
		int backwardStep = 0;
		for (int i = 0; i < (int)c.size(); i++) {
			std::string command = getCommand(c[i]);
			int value = getValue(c[i]);
			if (command == "forward") {
				forwardStep += value;
			}
			else if (command == "backward") {
				backwardStep += value;
			}
			else if (command == "left") {
				for (int j = 0; j < MAXANGLE; j++) tmp[j] = dp[j];
				for (int j = 0; j < MAXANGLE; j++) {
					if (!tmp[j]) continue;
					dp[(j + value) % MAXANGLE] = true;
				}
			}
			else if (command == "right") {
				for (int j = 0; j < MAXANGLE; j++) tmp[j] = dp[j];
				for (int j = 0; j < MAXANGLE; j++) {
					if (!tmp[j]) continue;
					dp[(j - value + MAXANGLE) % MAXANGLE] = true;
				}
			}
		}
		double answer = 0;
		for (int i = 0; i < MAXANGLE; i++) {
			if (!dp[i]) continue;
			double now = 0;
			now += forwardStep * forwardStep;
			now += backwardStep * backwardStep;
			now -= 2 * forwardStep * backwardStep * cos(i / 180.0 * pi);
			answer = std::max(answer, sqrt(now));
		}
		return answer;
	}
}T;

std::vector<std::string> vec;

int main() {
	vec.push_back("forward 100");
	vec.push_back("backward 100");
	vec.push_back("left 90");
	printf("%.10f\n", T.maxDistance(vec));
	return 0;
}
