#include <stdint.h>
#include <cmath>
#include <vector>
#include "vector.h"
#include "line.h"

#ifndef MAP_SHAPE_UTILS_POLYGON
#define MAP_SHAPE_UTILS_POLYGON

namespace map { namespace shapeutils {

using Vec = Vec2<double>;

class Polygon {
    public:
        Polygon() = default;
        ~Polygon() = default;
        Polygon& addVec(Vec&& rhs);
        size_t size() const;
        bool isInside(const Vec &rhs) const;
    protected:
    private:
        std::vector<Vec> points;
};

} // namespace shapeutils
} // namespace map

#endif // MAP_SHAPE_UTILS_POLYGON

