#include <iostream>

#include "ProjectDefines.h"
#include "EarthGrid.h"
#include "EarthConstants.h"
#include "RandomPointGenerator.h"

using namespace std;
using namespace project_defines;
using namespace earth_constants;

const int NUM_OF_LATITUDE = 2 * MAX_LATITUDE / NAME_PARAMETER;
const int NUM_OF_LONGITUDE = 2 * MAX_LONGITUDE / NAME_PARAMETER;

/*int discrete_earth[NUM_OF_LATITUDE][NUM_OF_LONGITUDE] = { 0 };
vector<Rectangle> population;
vector<Rectangle> nextPopulation;
*/

int main()
{
	cout << "Running..." << endl;	

	for (int i = 0; i < NUM_POINTS; ++i) {
		GeoPoint p = RandomPointGenerator::GetInstance().GetRandomPoint();

		p.latitude = lat(gen);
		p.longitude = lon(gen);

		int latIdx = static_cast<int>((p.latitude + MAX_LATITUDE) / NAME_PARAMETER);
		int lonIdx = static_cast<int>((p.longitude + MAX_LONGITUDE) / NAME_PARAMETER);
		//cout << p.latitude << " " << p.longitude << " " << latIdx << " " << lonIdx <<endl;
		++discrete_earth[latIdx][lonIdx];
		if (0 == (i % NUM_LOG)) {
			cout << "I = " << i << endl;
		}
	}

	cout << "Check Earth" << endl;
	int emptyCount = 0;
	for (int i = 0; i < NUM_OF_LATITUDE; ++i) {
		for (int j = 0; j < NUM_OF_LONGITUDE; ++j) {
			if (0 == discrete_earth[i][j]) {
				++emptyCount;
				//cout << "No points at " << i << " " << j << endl;
			}
		}
	}

	population.reserve(POPULATION_COUNT);
	nextPopulation.reserve(POPULATION_COUNT);
	for (int i = 0; i < POPULATION_COUNT; ++i) {
		Rectangle rect;
		std::uniform_real_distribution<> angle(0, _Pi);
		rect.p1.latitude = lat(gen);
		rect.p1.longitude = lon(gen);
		rect.p2.latitude = lat(gen);
		while (rect.p2.longitude < rect.p1.longitude) {
			rect.p2.longitude = lon(gen);
		}
		
		rect.p1.latIdx = static_cast<int>((rect.p1.latitude + MAX_LATITUDE) / NAME_PARAMETER);
		rect.p1.lonIdx = static_cast<int>((rect.p1.longitude + MAX_LONGITUDE) / NAME_PARAMETER);
		rect.p2.latIdx = static_cast<int>((rect.p1.latitude + MAX_LATITUDE) / NAME_PARAMETER);
		rect.p2.lonIdx = static_cast<int>((rect.p1.longitude + MAX_LONGITUDE) / NAME_PARAMETER);

		rect.alpha = angle(gen);
		//rect.fitness = 
		//int minLat = min(rect.p1.latIdx)
		//for(int )

		population.push_back(rect);
	
		rect.distance = (rect.p1.latitude - rect.p2.latitude) * (rect.p1.latitude - rect.p2.latitude) +
			(rect.p1.longitude - rect.p2.longitude) * (rect.p1.longitude - rect.p2.longitude);
		rect.square = rect.distance*sin(rect.alpha) / 2.0f;

		rect.fitness = rect.square / MAX_AREA;
	}

	cout << "Program finished " << emptyCount << endl;
    return 0;
}

