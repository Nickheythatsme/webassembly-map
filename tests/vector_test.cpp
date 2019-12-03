#include "gtest/gtest.h"
#include <iostream>
#include "../src/shape_utils/vector.h"
#include "../src/shape_utils/line.h"

using std::cout;
using std::endl;
using namespace map::shapeutils;
using Vd = Vec2<double>;
using Ld = Line<double>;

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vec2<T>& v) {
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}

TEST(Vector, Vector) {
    cout << "Vector test working!" << endl;
}

TEST(Vector, Equality) {
    Vd vd1 {1.0, 2.0};
    Vd vd2 {1.0, 2.0};
    Vd vd3 {1.0, 3.0};

    EXPECT_TRUE(vd1 == vd2);
    EXPECT_TRUE(vd1 != vd3);
    EXPECT_FALSE(vd1 == vd3);
} 

TEST(Vector, Assignment) {
    
    {
        Vd vd1 {1.0, 1.0};
        Vd vd2 {2.0, 2.0};
        vd1 = vd2;
        EXPECT_EQ(vd1, vd2);
    }
    {
        Vd vd1 {1.0, 1.0};
        Vd vd2 {2.0, 2.0};
        vd1 -= vd2;
        EXPECT_EQ(vd1.getX(), -1.0);
        EXPECT_EQ(vd1.getY(), -1.0);
    }
    {
        Vd vd1 {1.0, 1.0};
        Vd vd2 {2.0, 2.0};
        vd1 += vd2;
        EXPECT_EQ(vd1.getX(), 3.0);
        EXPECT_EQ(vd1.getY(), 3.0);
    }
    {
        Vd vd1 {2.0, 2.0};
        Vd vd2 {2.0, 2.0};
        vd1 *= vd2;
        EXPECT_EQ(vd1.getX(), 4.0);
        EXPECT_EQ(vd1.getY(), 4.0);
    }
}

TEST(Vector, ErrorAcceptance)
{
    Vd vd1 {1.0, 2.0};
    Vd vd2 {1.0 - 0.00049, 2.0};
    EXPECT_EQ(vd1, vd2);
}

TEST(Line, smoke) {
    Ld line { {1.0, 2.0}, {1.0, 2.0}};
}

TEST(Line, magnitude) {
    Ld line { {1.0, 2.0}, {1.0, 3.0}};

    EXPECT_EQ(line.magnitude(), 1);
}

TEST(Line, onLine) {
    Ld line1 { {0.0, 0.0}, {2.0, 2.0}};
    Vd valid_point1 {1.0, 1.0};
    Vd valid_point2 {0.0, 0.0};
    Vd valid_point3 {2.0, 2.0};
    Vd invalid_point {1.5, 1.0};

    EXPECT_TRUE(line1.onLine(valid_point1));
    EXPECT_TRUE(line1.onLine(valid_point2));
    EXPECT_TRUE(line1.onLine(valid_point3));
    EXPECT_FALSE(line1.onLine(invalid_point));
}
