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
    void Print(void);

    GeoPoint p1;
    GeoPoint p2;
    float alpha;

private:	
    //derived parameters
    GeoPoint p3;
    GeoPoint p4;
    float diagonal;
    float square;
    //float fitness;
};

