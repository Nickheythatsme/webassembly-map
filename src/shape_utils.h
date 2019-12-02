#include <stdint.h>
#include <memory>
#include <vector>

#ifndef MAP_SHAPE_UTILS
#define MAP_SHAPE_UTILS

struct Box {
  double x_min {};
  double x_max {};
  double y_min {};
  double y_max {};
};

class Vec2 {
  public:
    Vec2() = default;
    Vec2(double x, double y);
    double x {};
    double y {};
};

bool operator==(const Vec2 &lhs, const Vec2 &rhs);
Vec2 operator-(const Vec2 &lhs, const Vec2 &rhs);
Vec2 operator+(const Vec2 &lhs, const Vec2 &rhs);
Vec2 operator*(const Vec2 &lhs, const Vec2 &rhs);

Vec2 calc_direction(const Vec2 &from, const Vec2 &to);
double calc_magnitude(const Vec2 &v1);
bool calc_colinear(const Vec2 &a, const Vec2 &b, const Vec2 &c);
bool calc_on_line(const Vec2& start, const Vec2& to_test, const Vec2& end);

class Polygon {
    public:
        Polygon() = delete;
        Polygon(std::vector<Vec2>&& points);
        bool is_complete() const;
    protected:
    private:
        std::vector<Vec2> points;
};

#endif // MAP_SHAPE_UTILS
