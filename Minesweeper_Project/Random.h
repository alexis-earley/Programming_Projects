#pragma once
#include <random>
#include <ctime>

class Random { //we want to be able to use this class without an instance
//ex. in main: int value = Random::Number(2, 50);
//static variables/functions exist for the lifetime of your program
//like global variables but more intentional.  And they can be made private/protected
	static std::mt19937 random;
public:
	static int x; //won't be able to copy this
	//One and only one of this function- shared among all instances/belongs to the class itself
	static int Int(int min, int max);
};