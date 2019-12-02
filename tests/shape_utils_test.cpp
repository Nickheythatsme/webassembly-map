#include "gtest/gtest.h"
#include <iostream>
#include "../src/shape_utils.h"

using std::cout;
using std::endl;

std::ostream& operator<<(std::ostream& out, const Vec2 v) {
    out << "(" << v.x << ", " << v.y << ")";
    return out;
}

TEST(Direction, ShapeUtils) {
    Vec2 v1 {1.0, 2.0};
    Vec2 v2 {4.0, 5.0};

    cout << v1 << " " << v2 << endl;
    cout << calc_direction(v1, v2) << endl;
    ASSERT_EQ(calc_direction(v1, v2), Vec2(1, 1));
}


TEST(Colinear, ShapeUtils) {
    Vec2 v1 {1.0, 2.0};
    Vec2 v2 {2.0, 3.0};
    Vec2 v3 {4.0, 5.0};
    Vec2 bad_vec {4.0, 4.0};

    cout << calc_colinear(v1, v2, v3) << endl;
    ASSERT_TRUE(calc_colinear(v1, v2, v3));
    ASSERT_TRUE(calc_colinear(v2, v1, v3));
    ASSERT_TRUE(calc_colinear(v3, v2, v1));

    cout << calc_colinear(v1, v2, bad_vec) << endl;
    ASSERT_FALSE(calc_colinear(v1, v2, bad_vec));
}

TEST(OnLine, ShapeUtils) {
    Vec2 v1 {1.0, 2.0};
    Vec2 v2 {2.0, 3.0};
    Vec2 v3 {4.0, 5.0};

    ASSERT_TRUE(calc_on_line(v1, v2, v3));
    ASSERT_FALSE(calc_on_line(v1, v3, v2));
}

