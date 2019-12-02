#include <stdint.h>
#include <cmath>


#ifndef MAP_SHAPE_UTILS_LINE
#define MAP_SHAPE_UTILS_LINE

namespace map { namespace shapeutils {

template<typename T>
class Line
{
    public:
        Line() = default;
        Line(const Line &rhs) = default;
        Line(Line &&rhs) noexcept = default;
        Line(const Vec2<T>& start, const Vec2<T>& end):
            start(start), end(end)
        {}
        Line(Vec2<T> &&start, Vec2<T> &&end):
            start(std::move(start)), end(std::move(end))
        {}
        ~Line() = default;
        Vec2<T> direction() const
        {
            return calculate_direction(start, end);
        }
        T magnitude() const
        {
            return calculate_magnitude(end - start);
        }
        // TODO add error acceptance!
        bool onLine(const Vec2<T>& to_test) const
        {
            if (to_test == start || to_test == end)
            {
                return true;
            }
            auto result = Line<T>(start, to_test);
            if (result.magnitude() > magnitude())
            {
                return false;
            }
            if (result.direction() != direction())
            {
                return false;
            }
            return true;
        }
    private:
        static T calculate_magnitude(const Vec2<T>& to_test)
        {
            return sqrt((to_test.getX() * to_test.getX()) + (to_test.getY() * to_test.getY()));
        }
        static Vec2<T> calculate_direction(const Vec2<T>& start, const Vec2<T>& end)
        {
            T diff_x = end.getX() - start.getX();
            T diff_y = end.getY() - start.getY();
            T max_val = fmax(diff_x, diff_y);
            if (max_val == 0) {
                max_val = 1;
            }
            return Vec2<T>(diff_x/max_val, diff_y/max_val);
        }
        Vec2<T> start; // starting point
        Vec2<T> end; // ending point
};

/**
bool calc_colinear(const Vec2 &a, const Vec2 &b, const Vec2 &c);
bool calc_on_line(const Vec2& start, const Vec2& to_test, const Vec2& end);
*/

} // namespace shapeutils
} // namespace map

#endif //MAP_SHAPE_UTILS_LINE
