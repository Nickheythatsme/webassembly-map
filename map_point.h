#include <stdio.h>
#include <stdlib.h>

#ifndef MAP_POINT
#define MAP_POINT

class MapPoint {
    public:
        MapPoint() = default;
    private:
        float pos_and_color[3];
};
#endif
