#pragma once

class EarthGrid {
public:
	static EarthGrid& GetInstance()
	{
		static EarthGrid instance;
		return instance;
	}
       void AddPoint(int, int);
private:
	EarthGrid();
	EarthGrid(int, int);
	~EarthGrid();
	EarthGrid(const EarthGrid& root);
	EarthGrid& operator=(const EarthGrid&);

	int* grid;
	int sizeX;
	int sizeY;
};
