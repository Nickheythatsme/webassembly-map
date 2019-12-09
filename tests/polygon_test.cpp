#include "gtest/gtest.h"
#include <iostream>
#include "../src/shape_utils/polygon.h"

using std::cout;
using std::endl;
using namespace map::shapeutils;

using Vec = Vec2<double>;

TEST(Polygon, Smoke) {
    Polygon poly;
}

TEST(Polygon, AddVec) {
    Polygon poly;
    
    EXPECT_TRUE(poly.size() == 0);
    poly.addVec(Vec(1.0, 1.0));
    EXPECT_TRUE(poly.size() == 1);
}

TEST(Polygon, isInside) {
    Polygon poly;
    Vec vec {0,0};
    poly.addVec(Vec(-1.0, -1.0));
    poly.addVec(Vec(-1.0, 1.0));
    poly.addVec(Vec(1.0, 1.0));
    poly.addVec(Vec(1.0, -1.0));

    EXPECT_TRUE(poly.isInside(vec));

}
