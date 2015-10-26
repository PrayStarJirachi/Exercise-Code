#include <cstdio>
#include <vector>
#include <algorithm>

class FanFailure{
public:
	std::vector<int> getRange(std::vector <int> capacities, int minCooling) {
		std::sort(capacities.begin(), capacities.end());
		std::vector<int> answer;
		answer.resize(2);
		int totalCapacities = 0;
		for (int i = 0; i < (int)capacities.size(); i++) {
			totalCapacities += capacities[i];
		}
		answer[0] = answer[1] = 0;
		for (int i = 0, sum = 0; i < (int)capacities.size(); i++) {
			sum += capacities[i];
			if (totalCapacities - sum < minCooling) {
				answer[0] = i;
				break;
			}
		}
		for (int i = (int)capacities.size() - 1, sum = 0; i >= 0; i--) {
			sum += capacities[i];
			if (totalCapacities - sum < minCooling) {
				answer[1] = (int)capacities.size() - i - 1;
				break;
			}
		}
		return answer;
	}
};

int main() {
}
