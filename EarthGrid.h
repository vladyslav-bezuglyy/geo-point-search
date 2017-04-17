#pragma once

class EarthGrid {
public:
	static const EarthGrid& GetInstance()
	{
		static EarthGrid instance;
		return intstance;
	}
private:
	EarthGrid();
	~EarthGrid();
	EarthGrid(const EarthGrid& root);
	EarthGrid& operator=(const EarthGrid&);

	int** grid;
	int sizeX;
	int sizeY;
};
