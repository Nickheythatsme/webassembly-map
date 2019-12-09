//
// Created by Nick Grout on 2019-12-09.
//
#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../src/shape_utils/matrix.h"

using std::cout;
using std::endl;
using namespace map::shapeutils;

TEST(Matrix, Smoke) {
    Matrix<double> matrix {2, 3};
}

TEST(Matrix, Access) {
    Matrix<double> matrix {2, 3};
    cout << endl << matrix << endl;
    matrix.access(1, 2) = 4.0;
    cout << endl << matrix << endl;
    EXPECT_EQ(matrix.access(1, 2), 4.0);
}

TEST(Matrix, Iterators) {
    Matrix<double> matrix {2, 3};
    matrix.access(0,0) = 1.0;
    matrix.access(0,1) = 2.0;
    matrix.access(0,2) = 3.0;
    matrix.access(1,0) = 2.0;
    {
        std::stringstream ss;
        for (auto it = matrix.beginVerticle(0); it != matrix.endVerticle(0); ++it)
        {
            ss << *it << "\n";
        }
        cout << endl << ss.str() << endl;
        EXPECT_EQ(ss.str(), "1\n2\n3\n");
    }
    {
        std::stringstream ss;
        for (auto it = matrix.beginHorizontal(0); it != matrix.endHorizontal(0); ++it)
        {
            ss << *it << " ";
        }
        cout << endl << ss.str() << endl;
        EXPECT_EQ(ss.str(), "1 2 ");
    }
}
