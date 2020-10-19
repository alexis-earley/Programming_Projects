#include "Random.h"

//Don't have to redeclare something as static if you've already called it that
std::mt19937 random(time(0)); //gives you a new seed value each time

int Random::Int(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}