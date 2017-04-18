#include <random>
#include <iostream>
#include <fstream>
#include <cassert>
#include "EarthGrid.h"
#include "EarthConstants.h"
#include "ProjectDefines.h"

using namespace std;
using namespace earth_constants;
using namespace project_defines;

EarthGrid::EarthGrid(int sizeX_, int sizeY_) : sizeX(sizeX_), sizeY(sizeY_) {
        if (IS_DEBUG) {
                cout << "Initialize Earth grid " << sizeX_ << " " << sizeY_ << endl;
        }
	grid = new int[sizeX_*sizeY_];
	for (int i = 0; i < sizeX_*sizeY_; ++i) {
		grid[i] = 0;
	}
}

EarthGrid::~EarthGrid() {
	delete[] grid;
}

void EarthGrid::AddPoint(GeoPoint p) {
    int iX = p.lonIdx;
    int iY = p.latIdx;
    if (iY*sizeX + iX >= sizeX*sizeY) {
        cout << "Error " << p.latitude << " " << p.longitude << " " << iY << " " << iX << endl;
        if (iX >= sizeX) {
            iX = sizeX - 1;
        }
        if (iY >= sizeY) {
            iY = sizeY - 1;
        }
    }
    assert(iY*sizeX + iX < sizeX*sizeY);
    ++grid[iY*sizeX + iX];
}

void EarthGrid::PrintGrid(void) {
    ofstream f ("grid.txt");
    if (f.is_open()) {
        for(int i = 0; i < sizeX*sizeY; ++i) {
            f << grid[i] << " ";
        }
        f.close();
    } else {
        cout << "Unable to open file";
    }
}
