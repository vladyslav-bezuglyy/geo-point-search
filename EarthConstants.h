#pragma once

namespace earth_constants {
	const float MAX_LATITUDE = 90.0f;
	const float MAX_LONGITUDE = 180.0f;
	const float GRID_SIZE = 1.0f;
	const float MAX_AREA = MAX_LATITUDE * MAX_LONGITUDE * 4.0f;
	const float MAX_DISTANCE = sqrt(MAX_LATITUDE*MAX_LATITUDE * 4 + MAX_LONGITUDE*MAX_LONGITUDE * 4);
};
