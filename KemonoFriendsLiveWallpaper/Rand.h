#ifndef __KEMONO_FRIENDS_LIVE_WALLPAPER__RAND_H__
#define __KEMONO_FRIENDS_LIVE_WALLPAPER__RAND_H__


#include <random>




class Rand
{
public:
	Rand() = delete;


public:
	static std::mt19937 engine;


private:
	static std::uniform_int_distribution<> s_rndDist;


public:
	static float getRandomFloat();
};


#endif