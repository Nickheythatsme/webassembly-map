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
    // TODO implement
    return true;
}

} // namespace shapeutils
} // namespace map
