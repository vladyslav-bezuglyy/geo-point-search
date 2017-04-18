#pragma once

typedef struct GeoPoint_ {
	float latitude;
	float longitude;
	int latIdx;
	int lonIdx;
} GeoPoint;

class Rectangle {
public:
    Rectangle();
    ~Rectangle();

    float GetSquare(void) const;
    void Mutate(void);

    GeoPoint p1;
    GeoPoint p2;
    float side;
    //float alpha;

private:
    /*GeoPoint p1;
    GeoPoint p2;
    float alpha;*/
	
    //derived parameters
    float alpha;
    GeoPoint p3;
    GeoPoint p4;
    float diagonal;
    float square;
    //float fitness;
};

