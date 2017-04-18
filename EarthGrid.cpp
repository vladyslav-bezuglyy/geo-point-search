#include <random>
#include <iostream>
#include <cassert>
#include "EarthGrid.h"
#include "EarthConstants.h"
#include "ProjectDefines.h"

using namespace std;
using namespace earth_constants;
using namespace project_defines;

EarthGrid::EarthGrid(int sizeX_, int sizeY_) : sizeX(sizeX_), sizeY(sizeY_) {
	if (IS_DEBUG) {
		cout << "Initialize Earth grid" << endl;
	}
	grid = new int[sizeX_*sizeY_];
	for (int i = 0; i < sizeX_*sizeY_; ++i) {
		grid[i] = 0;
	}
}

EarthGrid::~EarthGrid() {
	delete[] grid;
}

void EarthGrid::AddPoint(int iX, int iY) {
	assert(iX >= 0 && iX < sizeX && iY >= 0 && iY < sizeY);
	//++grid[ix][iy];
}
