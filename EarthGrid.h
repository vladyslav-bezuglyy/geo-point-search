#pragma once

#include "GeoObjects.h"

class EarthGrid {
public:
    static EarthGrid& GetInstance()
    {
            static EarthGrid instance;
            return instance;
    }
        ~EarthGrid();
        void AddPoint(GeoPoint);
        void PrintGrid(void) const;
        int GetCount(int iX, int iY) const;
private:
        EarthGrid();
        EarthGrid(const EarthGrid& root);
        EarthGrid& operator=(const EarthGrid&);

        int* grid;
	int sizeX;
	int sizeY;
};
