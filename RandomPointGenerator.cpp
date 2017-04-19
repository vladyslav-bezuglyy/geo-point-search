#include <random>
#include <iostream>
#include "RandomPointGenerator.h"
#include "EarthConstants.h"
#include "ProjectDefines.h"

using namespace std;
using namespace earth_constants;
using namespace project_defines;

GeoPoint RandomPointGenerator::GetRandomPoint() {
    static default_random_engine gen(time(0));
    static uniform_real_distribution<float> lat(-MAX_LATITUDE, MAX_LATITUDE);
    static uniform_real_distribution<float> lon(-MAX_LONGITUDE, MAX_LONGITUDE);

	GeoPoint p = { 0,0 };

	p.latitude = lat(gen);
	p.longitude = lon(gen);
        p.latIdx = static_cast<int>((p.latitude + MAX_LATITUDE) / GRID_SIZE);
        p.lonIdx = static_cast<int>((p.longitude + MAX_LONGITUDE) / GRID_SIZE);
        if (IS_DEBUG) {
                cout << p.latitude << " " << p.longitude << " " << p.latIdx << " " << p.lonIdx << endl;
        }
	return p;
}
