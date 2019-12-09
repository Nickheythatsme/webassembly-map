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
        const Vec2<T>& getStart() const
        {
            return start;
        }
        const Vec2<T>& getEnd() const
        {
            return end;
        }
        ~Line() = default;
        Vec2<T> direction() const
        {
            return calculate_direction(start, end);
        }
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
            return !(result.direction() != direction());
        }
        bool linesIntersect(const Line<T>& rhs) const
        {
            // TODO fix linesIntersect
            auto b_1 = this->getStart().getY();
            auto b_2 = rhs.getStart().getY();
            auto m_1 = this->getM();
            auto m_2 = rhs.getM();
            auto x_intercept = (b_2 - b_1) / (m_1 - m_2);
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
    private:
        double getM() const
        {
            auto dir = direction();
            if (dir.getY() == 0) {
                return 0;
            }
            return dir.getX() / dir.getY();
        }
        static T calculate_magnitude(const Vec2<T>& to_test)
        {
            return sqrt((to_test.getX() * to_test.getX()) + (to_test.getY() * to_test.getY()));
        }
        static Vec2<T> calculate_direction(const Vec2<T>& start, const Vec2<T>& end)
        {
            T diff_x = end.getX() - start.getX();
            T diff_y = end.getY() - start.getY();
            return Vec2<T>(diff_x, diff_y);
        }
        Vec2<T> start; // starting point
        Vec2<T> end; // ending point
};

} // namespace shapeutils
} // namespace map

#endif //MAP_SHAPE_UTILS_LINE
