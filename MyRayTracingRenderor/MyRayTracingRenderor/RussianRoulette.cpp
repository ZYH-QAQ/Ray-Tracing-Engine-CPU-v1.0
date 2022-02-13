#include "RussianRoulette.h"
#include <cstdlib>
#include <random>
extern std::uniform_int_distribution<unsigned> rand3;
extern std::default_random_engine e;
bool RussianRoulette::Decide()
{
	if (rand3(e) <= 9)
		return true;
	else
		return false;
}