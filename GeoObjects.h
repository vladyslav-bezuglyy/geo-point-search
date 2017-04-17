#pragma once

typedef struct GeoPoint {
	float latitude;
	float longitude;
	int latIdx;
	int lonIdx;
};

typedef struct Rectangle {
	GeoPoint p1;
	GeoPoint p2;
	float alpha;
	
	//derived parameters
	GeoPoint p3;
	GeoPoint p4;
	float distance;	
	float square;
//	float fitness;
};