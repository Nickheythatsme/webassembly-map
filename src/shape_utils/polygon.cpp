#include "polygon.h"

namespace map { namespace shapeutils {
using Vec = Vec2<double>;

Polygon& Polygon::addVec(Vec&& rhs)
{
    points.emplace_back(std::move(rhs));
    return *this;
}

size_t Polygon::size() const
{
    return points.size();
}

using LineD = Line<double>;

bool Polygon::isInside(const Vec &rhs) const
{
    if (points.size() < 3) {
        return false;
    }
    size_t i = 0;
    size_t crosses = 0;
    LineD toTest = LineD(rhs, rhs + Vec(MAX_X, 0));
    LineD currentLine = LineD(points[i % points.size()], points[++i % points.size()]);
    do {
        if (toTest.linesIntersect(currentLine)) {
            ++crosses;
        }
    } while (currentLine.getStart() != points[0] && currentLine.getEnd() != points[0]);

    return true;
}

} // namespace shapeutils
} // namespace map
