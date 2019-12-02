#include "shape_utils.h"
#include <cmath>

Vec2::Vec2(double x, double y):
  y(y),
  x(x)
{ }

Vec2 calc_direction(const Vec2 &from, const Vec2 &to)
{
    double diff_x = to.x - from.x;
    double diff_y = to.y - from.y;
    double max_val = fmax(diff_x, diff_y);
    return Vec2(diff_x/max_val, diff_y/max_val);
}

double calc_magnitude(const Vec2 &v1)
{
    return sqrt((v1.x * v1.x) + (v1.y * v1.y));
}

bool calc_colinear(const Vec2 &a, const Vec2 &b, const Vec2 &c)
{
    Vec2 direction1 = calc_direction(a, b);
    Vec2 direction2 = calc_direction(a, c);
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

bool calc_on_line(const Vec2& start, const Vec2& to_test, const Vec2& end)
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

Vec2 operator-(const Vec2 &lhs, const Vec2 &rhs)
{
    return Vec2(
            lhs.x - rhs.x,
            lhs.y - rhs.y
            );
}

Vec2 operator+(const Vec2 &lhs, const Vec2 &rhs)
{
    return Vec2(
            lhs.x + rhs.x,
            lhs.y + rhs.y
            );
}

Vec2 operator*(const Vec2 &lhs, const Vec2 &rhs)
{
    return Vec2(
            lhs.x * rhs.x,
            lhs.y * rhs.y
            );
}

bool operator==(const Vec2&lhs, const Vec2 &rhs)
{
}

Polygon::Polygon(std::vector<Vec2>&& points):
    points(std::move(points))
{
}

bool Polygon::is_complete() const
{
    Vec2 starting_point = points[0];
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
    std::vector<Vec2> lines {points.size()};
}
