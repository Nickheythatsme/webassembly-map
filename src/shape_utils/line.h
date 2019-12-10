#include <stdint.h>
#include <cmath>
#include <limits>


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
        const Vec2<T>& getStart() const
        {
            return start;
        }
        const Vec2<T>& getEnd() const
        {
            return end;
        }
        ~Line() = default;
        T magnitude() const
        {
            return calculate_magnitude(end - start);
        }
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
            return !(result.getRateOfChange() != getRateOfChange());
        }
        bool linesIntersect(const Line<T>& rhs) const
        {
            // TODO implement
            return true;
        }
        // Operators
        Line<T>& operator=(const Line<T>& rhs)
        {
            start = rhs.start;
            end = rhs.end;
            return *this;
        }
        Line<T>& operator=(Line<T>&& rhs) noexcept
        {
            start = std::move(rhs.start);
            end = std::move(rhs.end);
            return *this;
        }
        friend bool operator==(const Line& lhs, const Line& rhs)
        {
            return lhs.getStart() == rhs.getStart() && lhs.getEnd() == rhs.getEnd();
        }
        friend bool operator!=(const Line& lhs, const Line& rhs)
        {
            return !(lhs == rhs);
        }
        T getRateOfChange() const
        {
            T diff_x = end.getX() - start.getX();
            T diff_y = end.getY() - start.getY();
            if (diff_y == 0) {
                return 0;
            }
            if (diff_x == 0) {
                return std::numeric_limits<T>::infinity();
            }
            return diff_x / diff_y;
        }
    private:
        static T calculate_magnitude(const Vec2<T>& to_test)
        {
            return sqrt((to_test.getX() * to_test.getX()) + (to_test.getY() * to_test.getY()));
        }
        Vec2<T> start; // starting point
        Vec2<T> end; // ending point
};

} // namespace shapeutils
} // namespace map

#endif //MAP_SHAPE_UTILS_LINE
