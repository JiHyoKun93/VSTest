#define _CRT_SECURE_NO_WARNINGS

#include "Environment.h"

int main() {

	srand(time(0));

	int results[100] = { 0, };
	int testSize = 100000;

	std::vector<float> weights = { 1,2,4,8};

	for (int i = 0; i < testSize; i++) {
		int result = throwDice(weights);
		//printf("%d\n", result);
		results[result] ++;
	}

	for (int i = 0; i < weights.size(); i++) {
		printf("%d / ÃâÇö : %d, È®·ü : %d\n", i, results[i], results[i] * 100 / testSize);
	}

	return 0;
}