#include <stdint.h>
#include <cstdlib>
#include <cmath>

#ifndef MAP_SHAPE_UTILS_VECTOR
#define MAP_SHAPE_UTILS_VECTOR

#define DOUBLE_ERROR_ACCEPTANCE 0.0005

namespace map { namespace shapeutils {

template<typename T=double>
class Vec2 {
  public:
    Vec2() = default;
    Vec2(const Vec2<T>& rhs): 
        x(rhs.x), y(rhs.y)
    { }
    Vec2(Vec2<T> &&rhs) noexcept :
        x(std::move(rhs.x)), y(std::move(rhs.y))
    { }
    ~Vec2() = default;
    Vec2(T x, T y) :
        x(x), y(y)
    { }
    friend bool operator==(const Vec2<T> &lhs, const Vec2<T> &rhs)
    {
        return (abs(lhs.x - rhs.x) < DOUBLE_ERROR_ACCEPTANCE) &&
            (abs(lhs.y - rhs.y) < DOUBLE_ERROR_ACCEPTANCE);
    }
    friend bool operator!=(const Vec2<T> &lhs, const Vec2<T> &rhs)
    {
        return !(lhs == rhs);
    }
    friend Vec2<T> operator-(const Vec2<T> &lhs, const Vec2<T> &rhs)
    {
        return Vec2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
    }
    friend Vec2<T> operator-(const Vec2<T> &lhs, const T &rhs)
    {
        return Vec2<T>(lhs.x - rhs, lhs.y - rhs);
    }
    friend Vec2<T> operator+(const Vec2<T> &lhs, const Vec2<T> &rhs)
    {
        return Vec2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    friend Vec2<T> operator+(const Vec2<T> &lhs, const T &rhs)
    {
        return Vec2<T>(lhs.x + rhs, lhs.y + rhs);
    }
    // Cross product
    friend Vec2<T> operator*(const Vec2<T> &lhs, const Vec2<T> &rhs)
    {
        return Vec2<T>(
                lhs.x * rhs.x, lhs.y * rhs.y
                );
    }
    friend Vec2<T> operator*(const Vec2<T> &lhs, const T &rhs)
    {
        return Vec2<T>(lhs.x * rhs, lhs.y * rhs);
    }
    Vec2<T>& operator=(const Vec2<T> &rhs)
    {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }
    Vec2<T>& operator+=(const Vec2<T> &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Vec2<T>& operator-=(const Vec2<T> &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    Vec2<T>& operator*=(const Vec2<T> &rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }
    const T& getX() const
    {
        return x;
    }
    T& getX()
    {
        return x;
    }
    const T& getY() const
    {
        return y;
    }
    T& getY()
    {
        return y;
    }
  protected:
    T x {};
    T y {};
};

} // namespace shapeutils
} // namespace map

/*

*/

#endif //MAP_SHAPE_UTILS_VECTOR


