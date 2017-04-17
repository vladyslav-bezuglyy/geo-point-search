#include <random>
#include "RandomPointGenerator.h"
#include "EarthConstants.h"
#include "ProjectDefines.h"

using namespace std;
using namespace earth_constants;
using namespace project_defines;

RandomPointGenerator::RandomPointGenerator() {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> lat(-MAX_LATITUDE, MAX_LATITUDE);
	uniform_real_distribution<> lon(-MAX_LONGITUDE, MAX_LONGITUDE);
}

RandomPointGenerator::GeoPoint GetRandomPoint() {
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