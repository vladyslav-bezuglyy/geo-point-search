#pragma once

class RandomPointGenerator {
public:
	static const RandomPointGenerator& GetInstance()
	{
		static RandomPointGenerator instance; 
		return intstance;
	}
	GeoPoint GetRandomPoint();
private:
	RandomPointGenerator();
	RandomPointGenerator(const RandomPointGenerator& root);
	RandomPointGenerator& operator=(const RandomPointGenerator&);
};