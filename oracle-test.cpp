#include <iostream>
#include <cmath>

#include "ProjectDefines.h"
#include "EarthGrid.h"
#include "EarthConstants.h"
#include "RandomPointGenerator.h"

using namespace std;
using namespace project_defines;
using namespace earth_constants;

//const int NUM_OF_LATITUDE = 2 * MAX_LATITUDE / NAME_PARAMETER;
//const int NUM_OF_LONGITUDE = 2 * MAX_LONGITUDE / NAME_PARAMETER;

/*int discrete_earth[NUM_OF_LATITUDE][NUM_OF_LONGITUDE] = { 0 };
vector<Rectangle> population;
vector<Rectangle> nextPopulation;
*/

vector<Rectangle> population;
vector<Rectangle> nextPopulation;

int main()
{
	cout << "Running..." << endl;	
        EarthGrid grid(2*MAX_LONGITUDE / GRID_SIZE, 2*MAX_LATITUDE / GRID_SIZE);
	for (int i = 0; i < NUM_POINTS; ++i) {
		GeoPoint p = RandomPointGenerator::GetInstance().GetRandomPoint();
                grid.AddPoint(p);
		if (0 == (i % NUM_LOG)) {
			cout << "I = " << i << endl;
		}
	}

        population.reserve(POPULATION_COUNT);
	nextPopulation.reserve(POPULATION_COUNT);

        Rectangle maxRect;
        float maxSquare = 0;
        default_random_engine gen(time(0));
        uniform_real_distribution<float> angle(0, M_PI);
        uniform_real_distribution<float> randIdx(0, 1.0f);

        for (int i = 0; i < POPULATION_COUNT; ++i) {		
                Rectangle rect;
                //rect.Print();
		population.push_back(rect);
                //cout << "Square " << rect.alpha << " " << rect.distance << " " << rect.square << endl;

                //rect.fitness = rect.square / MAX_AREA;
                if (rect.GetSquare() > maxSquare) {
                    maxSquare = rect.GetSquare();
                    maxRect = rect;
                }
        }

        for(int i = 0; i < GENERATION_COUNT; i++) {
            if (i % GENERATION_LOG) {
                cout << "Max " << maxSquare <<endl;
                maxRect.Print();
            }

            nextPopulation.clear();
            nextPopulation.push_back(maxRect); //one to preserve
            nextPopulation.push_back(maxRect); //one to mutate
            int count = 2;

            maxSquare = 0;
            for (int i = 0; i < POPULATION_COUNT; ++i) {

                int idx1 = randIdx(gen)*POPULATION_COUNT;
                int idx2 = randIdx(gen)*POPULATION_COUNT;

                if (population[idx1].GetSquare() > population[idx2].GetSquare()) {
                    nextPopulation.push_back(population[idx1]);
                } else {
                    nextPopulation.push_back(population[idx2]);
                }

                ++count;
                if (count >= POPULATION_COUNT) {
                    break;
                }
            }

            maxRect = nextPopulation[0];
            maxSquare = nextPopulation[0].GetSquare();
            for (int i = 1; i < POPULATION_COUNT; ++i) {
                float mutation = randIdx(gen);
                if (mutation > 0.5) {
                    nextPopulation[i].Mutate();
                }
                if (nextPopulation[i].GetSquare() > maxSquare) {
                    maxSquare = nextPopulation[i].GetSquare();
                    maxRect = nextPopulation[i];
                }
            }

            population.clear();
            population = nextPopulation;
        }
        cout << "Total max " << maxSquare << endl;
        grid.PrintGrid();
        cout << "Program finished " << endl;
    return 0;
}

