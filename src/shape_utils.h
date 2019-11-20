#include <memory>
#include <stdint.h>

#ifndef MAP_SHAPE_UTILS
#define MAP_SHAPE_UTILS

struct Box {
  double x_min {};
  double x_max {};
  double y_min {};
  double y_max {};
};

class Vec2d {
  public:
    Vec2d() = default;
    Vec2d(double x, double y);
    double x {};
    double y {};
};

bool operator==(const Vec2d &lhs, const Vec2d &rhs);
Vec2d operator-(const Vec2d &lhs, const Vec2d &rhs);
Vec2d operator+(const Vec2d &lhs, const Vec2d &rhs);

Vec2d calc_direction(const Vec2d &from, const Vec2d &to);
double calc_magnitude(const Vec2d &v1);
bool calc_colinear(const Vec2d &a, const Vec2d &b, const Vec2d &c);
bool calc_on_line(const Vec2d& start, const Vec2d& to_test, const Vec2d& end);


class Polygon {
    public:
        Polygon();
    protected:
    private:
        std::unique_ptr<Vec2d[]> points;
        uint32_t num_points;
};

#endif // MAP_SHAPE_UTILS
