#pragma once

typedef struct GeoPoint_ {
    float latitude;
    float longitude;
    int latIdx;
    int lonIdx;
} GeoPoint;

enum FitnessType {
    MAX_EMPTY_RECTANGLE,
    MIN_FILLED_RECTANGLE,
    FITNESS_TYPE_COUNT
};

class Rectangle {
public:
    Rectangle(FitnessType fitType);
    Rectangle() {};
    ~Rectangle();

    float GetSquare(void) const;
    float GetFitness(void) const;
    float GetPointCount(void) const;

    void Mutate(void);
    bool InThis(GeoPoint p) const;
    void Print(void) const;

    GeoPoint p1;
    GeoPoint p2;
    float alpha;

private:
    //derived parameters
    GeoPoint p3;
    GeoPoint p4;
    float diagonal;
    float square;
    float fitness;
    int pointCount;
    FitnessType fitType;

    void CalcFitness(void);
};

