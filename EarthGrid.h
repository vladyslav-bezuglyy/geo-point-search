#pragma once

#include "GeoObjects.h"

class EarthGrid {
public:
        EarthGrid(int, int);
        ~EarthGrid();
        void AddPoint(GeoPoint);
        void PrintGrid(void);
private:
        int* grid;
	int sizeX;
	int sizeY;
};
