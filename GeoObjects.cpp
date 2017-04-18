#include <random>
#include <iostream>
#include "GeoObjects.h"
#include "EarthGrid.h"
#include "EarthConstants.h"
#include "RandomPointGenerator.h"
#include "ProjectDefines.h"

using namespace std;
using namespace earth_constants;
using namespace project_defines;

Rectangle::Rectangle() {
    static default_random_engine gen(time(0));
    static uniform_real_distribution<float> angle(0, M_PI);
    static uniform_real_distribution<float> dist(GRID_SIZE, sqrt(MAX_DISTANCE_SQUARE));

    while(true) {
        p1 = RandomPointGenerator::GetInstance().GetRandomPoint();
        p2 = RandomPointGenerator::GetInstance().GetRandomPoint();
        while(p2.longitude < p1.longitude) {
            p2 = RandomPointGenerator::GetInstance().GetRandomPoint();
        }
        /*alpha = angle(gen);
        distance = (p1.latitude - p2.latitude) * (p1.latitude - p2.latitude) +
                (p1.longitude - p2.longitude) * (p1.longitude - p2.longitude);*/
        side = dist(gen);

        /*p3.latitude = p1.latitude - (sqrt(distance)/2.0f)*(1-cos(alpha));
        p3.longitude = p1.longitude - (sqrt(distance)/2.0f)*sin(alpha);
        if ((p3.latitude >= MAX_LATITUDE) || (p3.latitude <= -MAX_LATITUDE) ||
            (p3.longitude >= MAX_LATITUDE) || (p3.longitude <= -MAX_LONGITUDE)) {
            continue;
        }

        p4.latitude = p1.latitude - (sqrt(distance)/2.0f)*(1-cos(alpha));
        p4.longitude = p1.longitude - (sqrt(distance)/2.0f)*sin(alpha);
        if ((p4.latitude >= MAX_LATITUDE) || (p4.latitude <= -MAX_LATITUDE) ||
            (p4.longitude >= MAX_LATITUDE) || (p4.longitude <= -MAX_LONGITUDE)) {
            continue;
        }*/
    }
    square = distance*sin(alpha) / 2.0f;
}

Rectangle::~Rectangle() {

}

float Rectangle::GetSquare(void) const {
    return square;
}

void Rectangle::Mutate(void) {
    static default_random_engine gen(time(0));
    static uniform_real_distribution<float> randIdx(0, 1.0f);
    static uniform_real_distribution<float> randAngle(-0.1, 0.1f);
    static uniform_real_distribution<float> randPos(-2.0f, 2.0f);

    alpha += randAngle(gen);
    if (alpha > M_PI) {
        alpha -= M_PI;
    } else if (alpha < 0) {
        alpha += M_PI;
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

    p1.latIdx = static_cast<int>((p1.latitude + MAX_LATITUDE) / GRID_SIZE);
    p1.lonIdx = static_cast<int>((p1.longitude + MAX_LONGITUDE) / GRID_SIZE);
    p2.latIdx = static_cast<int>((p2.latitude + MAX_LATITUDE) / GRID_SIZE);
    p2.lonIdx = static_cast<int>((p2.longitude + MAX_LONGITUDE) / GRID_SIZE);

    distance = (p1.latitude - p2.latitude) * (p1.latitude - p2.latitude) +
            (p1.longitude - p2.longitude) * (p1.longitude - p2.longitude);
    square = distance*sin(alpha) / 2.0f;
}
