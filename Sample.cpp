#include <iostream>
#include <cmath>
#include <climits>

#include "ProjectDefines.h"
#include "EarthGrid.h"
#include "EarthConstants.h"
#include "RandomPointGenerator.h"

using namespace std;
using namespace project_defines;
using namespace earth_constants;

vector<Rectangle> population;
vector<Rectangle> nextPopulation;

int main()
{
    cout << "Generating points..." << endl;

    for (int i = 0; i < NUM_POINTS; ++i) {
        GeoPoint p = RandomPointGenerator::GetInstance().GetRandomPoint();
        EarthGrid::GetInstance().AddPoint(p);
        if (0 == (i % NUM_LOG)) {
            cout << "I = " << i << endl;
        }
    }
    EarthGrid::GetInstance().PrintGrid();

    population.reserve(POPULATION_COUNT);
    nextPopulation.reserve(POPULATION_COUNT);

    Rectangle bestRect;
    float bestFitness = INT_MAX;
    float square = 0;
    default_random_engine gen(time(0));
    uniform_real_distribution<float> angle(0, M_PI);
    uniform_real_distribution<float> randIdx(0, 1.0f);

    cout << "Generating initial population..." << endl;
    for (int i = 0; i < POPULATION_COUNT; ++i) {
        Rectangle rect(MAX_EMPTY_RECTANGLE);
        //Rectangle rect(MIN_FILLED_RECTANGLE);
        population.push_back(rect);
        if (rect.GetFitness() < bestFitness) {
            square = rect.GetSquare();
            bestFitness = rect.GetFitness();
            bestRect = rect;
        }
    }
    cout << "Running..." << endl;
    for(int i = 0; i < GENERATION_COUNT; ++i) {
        if (i % GENERATION_LOG) {
            cout << "Fitness: " << bestFitness <<" Square: " << square << " Count: "<<bestRect.GetPointCount() << endl;
            bestRect.Print();
        }
        nextPopulation.clear();
        nextPopulation.push_back(bestRect); //one to preserve
        nextPopulation.push_back(bestRect); //one to mutate

        Rectangle randomRect(MAX_EMPTY_RECTANGLE); //one random
        nextPopulation.push_back(randomRect);

        int count = 3;
        bestFitness = 0;
        for (int i = 0; i < POPULATION_COUNT; ++i) {
            int idx1 = randIdx(gen)*POPULATION_COUNT;
            int idx2 = randIdx(gen)*POPULATION_COUNT;

            if (population[idx1].GetFitness() < population[idx2].GetFitness()) {
                nextPopulation.push_back(population[idx1]);
            } else {
                nextPopulation.push_back(population[idx2]);
            }

            ++count;
            if (count >= POPULATION_COUNT) {
                    break;
                }
        }

        bestRect = nextPopulation[0];
        bestFitness = nextPopulation[0].GetFitness();
        square = nextPopulation[0].GetSquare();
        for (int i = 1; i < POPULATION_COUNT; ++i) {
            float mutation = randIdx(gen);
            if (mutation > 0.5) {
                nextPopulation[i].Mutate();
            }
            if (nextPopulation[i].GetFitness() < bestFitness) {
                square = nextPopulation[i].GetSquare();
                bestFitness = nextPopulation[i].GetFitness();
                bestRect = nextPopulation[i];
            }
        }

        population.clear();
        population = nextPopulation;
    }
    cout << "Program finished " << endl;
    return 0;
}

