#include "Rand.h"




std::mt19937 Rand::engine{ std::random_device()() };

std::uniform_int_distribution<> Rand::s_rndDist;

//###################################################################################################

float Rand::getRandomFloat()
{
	int randInt = s_rndDist(engine) - s_rndDist.max() / 2;

	return (static_cast<float>(randInt) / static_cast<float>(s_rndDist.max() / 2));
}

