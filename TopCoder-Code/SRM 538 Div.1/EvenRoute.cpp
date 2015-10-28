#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

class EvenRoute{
public:
	std::string isItPossible(std::vector<int> x, std::vector<int> y, int wantedParity) {
		for (int i = 0; i < (int)x.size(); i++) {
			if (((x[i] + y[i]) & 1) == wantedParity) {
				return "CAN";
			}
		}
		return "CANNOT";
	}
};

int main() {
}
