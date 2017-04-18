#pragma once

typedef struct GeoPoint_ {
	float latitude;
	float longitude;
	int latIdx;
	int lonIdx;
} GeoPoint;

typedef struct Rectangle_ {
	GeoPoint p1;
	GeoPoint p2;
	float alpha;
	
	//derived parameters
	GeoPoint p3;
	GeoPoint p4;
	float distance;	
	float square;
//	float fitness;
} Rectangle;