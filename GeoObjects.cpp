#include <random>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>
#include "GeoObjects.h"
#include "EarthGrid.h"
#include "EarthConstants.h"
#include "RandomPointGenerator.h"
#include "ProjectDefines.h"

using namespace std;
using namespace earth_constants;
using namespace project_defines;

Rectangle::Rectangle(FitnessType fitType_) {
    static default_random_engine gen(time(0));
    static uniform_real_distribution<float> angle(0, M_PI);

    fitType = fitType_;
    while(true) {
        p1 = RandomPointGenerator::GetInstance().GetRandomPoint();
        p2 = RandomPointGenerator::GetInstance().GetRandomPoint();
        if (p2.longitude >= p1.longitude) {
            continue;
        }
        alpha = angle(gen);
        diagonal = (p1.latitude - p2.latitude) * (p1.latitude - p2.latitude) +
                (p1.longitude - p2.longitude) * (p1.longitude - p2.longitude);

        p3.longitude = 0.5f*(p1.longitude*cos(alpha)+p1.longitude+fabs(sin(alpha)*(p1.latitude-p2.latitude))-p2.longitude*cos(alpha)+p2.longitude);
        p3.latitude = 0.5f*(-p1.longitude*fabs(sin(alpha)*(p1.latitude-p2.latitude))+p1.latitude*p1.latitude*cos(alpha)+p1.latitude*p1.latitude
                            +p2.longitude*fabs(sin(alpha)*(p1.latitude-p2.latitude))-2.0f*p1.latitude*p2.latitude*cos(alpha)+p2.latitude*p2.latitude*cos(alpha)-p2.latitude*p2.latitude)/(p1.latitude-p2.latitude);

        if ((p3.latitude >= MAX_LATITUDE) || (p3.latitude <= -MAX_LATITUDE) ||
            (p3.longitude >= MAX_LONGITUDE) || (p3.longitude <= -MAX_LONGITUDE)) {
            continue;
        }

        p4.longitude = 0.5f*(-p1.longitude*cos(alpha)+p1.longitude-fabs(sin(alpha)*(p1.latitude-p2.latitude))+p2.longitude*cos(alpha)+p2.longitude);
        p4.latitude = 0.5f*(p1.longitude*fabs(sin(alpha)*(p1.latitude-p2.latitude))-p1.latitude*p1.latitude*cos(alpha)+p1.latitude*p1.latitude
                            -p2.longitude*fabs(sin(alpha)*(p1.latitude-p2.latitude))+2.0*p1.latitude*p2.latitude*cos(alpha)-p2.latitude*p2.latitude*cos(alpha)-p2.latitude*p2.latitude)/(p1.latitude-p2.latitude);
        if ((p4.latitude >= MAX_LATITUDE) || (p4.latitude <= -MAX_LATITUDE) ||
            (p4.longitude >= MAX_LONGITUDE) || (p4.longitude <= -MAX_LONGITUDE)) {
            continue;
        }

        p3.latIdx = static_cast<int>((p3.latitude + MAX_LATITUDE) / GRID_SIZE);
        p3.lonIdx = static_cast<int>((p3.longitude + MAX_LONGITUDE) / GRID_SIZE);
        p4.latIdx = static_cast<int>((p4.latitude + MAX_LATITUDE) / GRID_SIZE);
        p4.lonIdx = static_cast<int>((p4.longitude + MAX_LONGITUDE) / GRID_SIZE);

        break;
    }
    square = diagonal*sin(alpha) / 2.0f;
    CalcFitness();
}

Rectangle::~Rectangle() {

}

float Rectangle::GetSquare(void) const {
    return square;
}

float Rectangle::GetFitness(void) const {
    return fitness;
}

float Rectangle::GetPointCount(void) const {
    return pointCount;
}

bool Rectangle::InThis(GeoPoint point) const {
   //Check the area of the triangles and compare it the area of the rectangle


    float a = sqrt((point.longitude - p1.longitude)*(point.longitude - p1.longitude) +
                   (point.latitude - p1.latitude)*(point.latitude - p1.latitude));
    float b = sqrt((point.longitude - p3.longitude)*(point.longitude - p3.longitude) +
                   (point.latitude - p3.latitude)*(point.latitude - p3.latitude));
    float c = sqrt((p1.longitude - p3.longitude)*(p1.longitude - p3.longitude) +
                   (p1.latitude - p3.latitude)*(p1.latitude - p3.latitude));
    float p = (a+b+c)/2.0f;
    float s1 = sqrt(p*(p-a)*(p-b)*(p-c));

    a = sqrt((point.longitude - p3.longitude)*(point.longitude - p3.longitude) +
                   (point.latitude - p3.latitude)*(point.latitude - p3.latitude));
    b = sqrt((point.longitude - p2.longitude)*(point.longitude - p2.longitude) +
                   (point.latitude - p2.latitude)*(point.latitude - p2.latitude));
    c = sqrt((p2.longitude - p3.longitude)*(p2.longitude - p3.longitude) +
                   (p2.latitude - p3.latitude)*(p2.latitude - p3.latitude));
    p = (a+b+c)/2.0f;
    float s2 = sqrt(p*(p-a)*(p-b)*(p-c));

    a = sqrt((point.longitude - p4.longitude)*(point.longitude - p4.longitude) +
                   (point.latitude - p4.latitude)*(point.latitude - p4.latitude));
    b = sqrt((point.longitude - p2.longitude)*(point.longitude - p2.longitude) +
                   (point.latitude - p2.latitude)*(point.latitude - p2.latitude));
    c = sqrt((p2.longitude - p4.longitude)*(p2.longitude - p4.longitude) +
                   (p2.latitude - p4.latitude)*(p2.latitude - p4.latitude));
    p = (a+b+c)/2.0f;
    float s3 = sqrt(p*(p-a)*(p-b)*(p-c));

    a = sqrt((point.longitude - p4.longitude)*(point.longitude - p4.longitude) +
                   (point.latitude - p4.latitude)*(point.latitude - p4.latitude));
    b = sqrt((point.longitude - p1.longitude)*(point.longitude - p1.longitude) +
                   (point.latitude - p1.latitude)*(point.latitude - p1.latitude));
    c = sqrt((p1.longitude - p4.longitude)*(p1.longitude - p4.longitude) +
                   (p1.latitude - p4.latitude)*(p1.latitude - p4.latitude));
    p = (a+b+c)/2.0f;
    float s4 = sqrt(p*(p-a)*(p-b)*(p-c));

    if (s1+s2+s3+s4 > square) {
        return false;
    }

    return true;
}

void Rectangle::Mutate(void) {
    static default_random_engine gen(time(0));
    static uniform_real_distribution<float> randIdx(0, 1.0f);
    static uniform_real_distribution<float> randAngle(-0.1, 0.1f);
    static uniform_real_distribution<float> randPos(-2.0f, 2.0f);

    while(true) {
        if (randIdx(gen) > 0.5) {
            alpha += randAngle(gen);
            if (alpha > M_PI) {
                alpha -= M_PI;
            } else if (alpha < 0) {
                alpha += M_PI;
            }
        }

        p1.latitude += randPos(gen);
        p1.longitude += randPos(gen);
        while(p1.latitude >= MAX_LATITUDE) {
            p1.latitude -= 1.0f;
        }
        while(p1.longitude >= MAX_LONGITUDE) {
            p1.longitude -= 1.0f;
        }
        while(p1.latitude <= -MAX_LATITUDE) {
            p1.latitude += 1.0f;
        }
        while(p1.longitude < -MAX_LONGITUDE) {
            p1.longitude += 1.0f;
        }

        p2.latitude += randPos(gen);
        p2.longitude += randPos(gen);
        while(p2.latitude >= MAX_LATITUDE) {
            p2.latitude -= 1.0f;
        }
        while(p2.longitude >= MAX_LONGITUDE) {
            p2.longitude -= 1.0f;
        }
        while(p2.latitude <= -MAX_LATITUDE) {
            p2.latitude += 1.0f;
        }
        while(p2.longitude <= -MAX_LONGITUDE) {
            p2.longitude += 1.0f;
        }

        p3.longitude = 0.5f*(p1.longitude*cos(alpha)+p1.longitude+fabs(sin(alpha)*(p1.latitude-p2.latitude))-p2.longitude*cos(alpha)+p2.longitude);
        p3.latitude = 0.5f*(-p1.longitude*fabs(sin(alpha)*(p1.latitude-p2.latitude))+p1.latitude*p1.latitude*cos(alpha)+p1.latitude*p1.latitude
                            +p2.longitude*fabs(sin(alpha)*(p1.latitude-p2.latitude))-2.0f*p1.latitude*p2.latitude*cos(alpha)+p2.latitude*p2.latitude*cos(alpha)-p2.latitude*p2.latitude)/(p1.latitude-p2.latitude);

        if ((p3.latitude >= MAX_LATITUDE) || (p3.latitude <= -MAX_LATITUDE) ||
                (p3.longitude >= MAX_LONGITUDE) || (p3.longitude <= -MAX_LONGITUDE)) {
            continue;
        }

        p4.longitude = 0.5f*(-p1.longitude*cos(alpha)+p1.longitude-fabs(sin(alpha)*(p1.latitude-p2.latitude))+p2.longitude*cos(alpha)+p2.longitude);
        p4.latitude = 0.5f*(p1.longitude*fabs(sin(alpha)*(p1.latitude-p2.latitude))-p1.latitude*p1.latitude*cos(alpha)+p1.latitude*p1.latitude
                            -p2.longitude*fabs(sin(alpha)*(p1.latitude-p2.latitude))+2.0f*p1.latitude*p2.latitude*cos(alpha)-p2.latitude*p2.latitude*cos(alpha)-p2.latitude*p2.latitude)/(p1.latitude-p2.latitude);
        if ((p4.latitude >= MAX_LATITUDE) || (p4.latitude <= -MAX_LATITUDE) ||
                (p4.longitude >= MAX_LONGITUDE) || (p4.longitude <= -MAX_LONGITUDE)) {
            continue;
        }
        break;
    }

    p1.latIdx = static_cast<int>((p1.latitude + MAX_LATITUDE) / GRID_SIZE);
    p1.lonIdx = static_cast<int>((p1.longitude + MAX_LONGITUDE) / GRID_SIZE);
    p2.latIdx = static_cast<int>((p2.latitude + MAX_LATITUDE) / GRID_SIZE);
    p2.lonIdx = static_cast<int>((p2.longitude + MAX_LONGITUDE) / GRID_SIZE);
    p3.latIdx = static_cast<int>((p3.latitude + MAX_LATITUDE) / GRID_SIZE);
    p3.lonIdx = static_cast<int>((p3.longitude + MAX_LONGITUDE) / GRID_SIZE);
    p4.latIdx = static_cast<int>((p4.latitude + MAX_LATITUDE) / GRID_SIZE);
    p4.lonIdx = static_cast<int>((p4.longitude + MAX_LONGITUDE) / GRID_SIZE);

    diagonal = (p1.latitude - p2.latitude) * (p1.latitude - p2.latitude) +
            (p1.longitude - p2.longitude) * (p1.longitude - p2.longitude);
    square = diagonal*sin(alpha) / 2.0f;
    CalcFitness();
}

void Rectangle::Print(void) const {
    cout<<"Rectangle: "<<"("<<p1.latitude<<", "<<p1.longitude<<"), ("<<
          p2.latitude<<", "<<p2.longitude<<"), ("<<
          p3.latitude<<", "<<p3.longitude<<"), ("<<
          p4.latitude<<", "<<p4.longitude<<"), alpha = "<<alpha<<endl;
}

void Rectangle::CalcFitness(void) {

    switch(fitType) {
    case MAX_EMPTY_RECTANGLE: {
        fitness = (1 - square/MAX_AREA);
        assert(fitness >= 0);

        int iX[] = {p1.lonIdx, p2.lonIdx, p3.lonIdx, p4.lonIdx};
        int iY[] = {p1.latIdx, p2.latIdx, p3.latIdx, p4.latIdx};
        int minIx = *min_element(iX, iX+4);
        int minIy = *min_element(iY, iY+4);
        int maxIx = *max_element(iX, iX+4);
        int maxIy = *max_element(iY, iY+4);

        pointCount = 0;
        for(int i = minIx; i < maxIx + 1; ++i) {
            for(int j = minIy; j < maxIy + 1; ++j) {
                GeoPoint point;
                point.longitude = -MAX_LONGITUDE+i*GRID_SIZE;
                point.latitude = -MAX_LATITUDE+j*GRID_SIZE;
                if (InThis(point)) {
                    pointCount += EarthGrid::GetInstance().GetCount(i, j);
                }
            }
        }
        fitness += ((static_cast<float>(pointCount))/NUM_POINTS)*CONSTRAINT_COEFF;
        break;
    }
    case MIN_FILLED_RECTANGLE: {
        fitness = (square/MAX_AREA);
        assert(fitness >= 0);

        int iX[] = {p1.lonIdx, p2.lonIdx, p3.lonIdx, p4.lonIdx};
        int iY[] = {p1.latIdx, p2.latIdx, p3.latIdx, p4.latIdx};
        int minIx = *min_element(iX, iX+4);
        int minIy = *min_element(iY, iY+4);
        int maxIx = *max_element(iX, iX+4);
        int maxIy = *max_element(iY, iY+4);

        pointCount = 0;
        for(int i = minIx; i < maxIx + 1; ++i) {
            for(int j = minIy; j < maxIy + 1; ++j) {
                GeoPoint point;
                point.longitude = -MAX_LONGITUDE+i*GRID_SIZE;
                point.latitude = -MAX_LATITUDE+j*GRID_SIZE;
                if (InThis(point)) {
                    pointCount += EarthGrid::GetInstance().GetCount(i, j);
                }
            }
        }
        float tolerance = fabs((static_cast<float>(pointCount)) / NUM_POINTS - REQUIRED_FRACTION);
        if (tolerance > REQUIRED_TOLERANCE) {
            fitness += (10.0f*CONSTRAINT_COEFF);
        } else {
            fitness += (CONSTRAINT_COEFF * (tolerance/REQUIRED_TOLERANCE));
        }

        break;
    }
    default:
        break;
    }
}
