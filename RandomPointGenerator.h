#pragma once

#include <random>
#include "GeoObjects.h"

class RandomPointGenerator {
public:
	static RandomPointGenerator& GetInstance()
	{
		static RandomPointGenerator instance; 
		return instance;
	}
	GeoPoint GetRandomPoint();
private:
	RandomPointGenerator();
	RandomPointGenerator(const RandomPointGenerator& root);
	RandomPointGenerator& operator=(const RandomPointGenerator&);

	std::default_random_engine gen;
	std::uniform_real_distribution<float> lat;
	std::uniform_real_distribution<float> lon;
};