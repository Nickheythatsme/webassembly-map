#include "shape_utils.h"
#include <cmath>

Vec2d::Vec2d(double x, double y):
  y(y),
  x(x)
{ }

Vec2d calc_direction(const Vec2d &from, const Vec2d &to)
{
    double diff_x = to.x - from.x;
    double diff_y = to.y - from.y;
    double max_val = fmax(diff_x, diff_y);
    return Vec2d(diff_x/max_val, diff_y/max_val);
}

double calc_magnitude(const Vec2d &v1)
{
    return sqrt((v1.x * v1.x) + (v1.y * v1.y));
}

bool calc_colinear(const Vec2d &a, const Vec2d &b, const Vec2d &c)
{
    Vec2d direction1 = calc_direction(a, b);
    Vec2d direction2 = calc_direction(a, c);
    double ratio1 = direction1.x / direction1.y;
    double ratio2 = direction2.x / direction2.y;

    if (ratio1 < 0) {
        ratio1 *= -1;
    }
    if (ratio2 < 0) {
        ratio2 *= -2;
    }

    return ratio1 == ratio2;
}

bool calc_on_line(const Vec2d& start, const Vec2d& to_test, const Vec2d& end)
{
    // See if it's colinear
    if (!calc_colinear(start, to_test, end)) {
        return false;
    }
    // See if the point is on the line by calculating magnitude
    double start_to_end = calc_magnitude(start - end);
    double test_to_start = calc_magnitude(start - to_test);
    return start_to_end >= test_to_start;
}

Vec2d operator-(const Vec2d &lhs, const Vec2d &rhs)
{
    return Vec2d(
            lhs.x - rhs.x,
            lhs.y - rhs.y
            );
}

Vec2d operator+(const Vec2d &lhs, const Vec2d &rhs)
{
    return Vec2d(
            lhs.x + rhs.x,
            lhs.y + rhs.y
            );
}

Vec2d operator*(const Vec2d &lhs, const Vec2d &rhs)
{
    return Vec2d(
            lhs.x * rhs.x,
            lhs.y * rhs.y
            );
}

bool operator==(const Vec2d&lhs, const Vec2d &rhs)
{
    return rhs.x == lhs.x && rhs.y == lhs.y;
}

Polygon::Polygon(std::vector<Vec2d>&& points):
    points(std::move(points))
{
}

bool Polygon::is_complete() const
{
    Vec2d starting_point = points[0];
    int starting_point_count = 0;
    for (const auto& vec: points)
    {
        if (vec == starting_point) {
            ++starting_point_count;
        }
    }
    if (starting_point_count != 2) {
        return false;
    }
    // make sure lines do not cross
    std::vector<Vec2d> lines {points.size()};
}
