#include <random>
#include <iostream>
#include "RandomPointGenerator.h"
#include "EarthConstants.h"
#include "ProjectDefines.h"

using namespace std;
using namespace earth_constants;
using namespace project_defines;

RandomPointGenerator::RandomPointGenerator() : gen(), lat(-MAX_LATITUDE, MAX_LATITUDE), lon(-MAX_LONGITUDE, MAX_LONGITUDE) {
}

GeoPoint RandomPointGenerator::GetRandomPoint() {
	GeoPoint p = { 0,0 };

	p.latitude = lat(gen);
	p.longitude = lon(gen);

	int latIdx = static_cast<int>((p.latitude + MAX_LATITUDE) / GRID_SIZE);
	int lonIdx = static_cast<int>((p.longitude + MAX_LONGITUDE) / GRID_SIZE);
	if (IS_DEBUG) {
		cout << p.latitude << " " << p.longitude << " " << latIdx << " " << lonIdx << endl;
	}
	return p;
}