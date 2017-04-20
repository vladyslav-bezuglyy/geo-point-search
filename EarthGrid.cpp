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

EarthGrid::EarthGrid() : sizeX(2*MAX_LONGITUDE / GRID_SIZE), sizeY(2*MAX_LATITUDE / GRID_SIZE) {
    if (IS_DEBUG) {
            cout << "Initialize Earth grid " << sizeX << " " << sizeY << endl;
    }
    grid = new int[sizeX*sizeY];
    for (int i = 0; i < sizeX*sizeY; ++i) {
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
        //Possible that random generate value of right boundary - bug in STL
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

int EarthGrid::GetCount(int iX, int iY) const {
    //assert(iY*sizeX + iX < sizeX*sizeY);
    if (iY*sizeX + iX < sizeX*sizeY) {
        return grid[iY*sizeX + iX];
    } else {
        return 0;
    }
}

void EarthGrid::PrintGrid(void) const {
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
