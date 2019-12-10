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

void test(const Matrix<double> &matrix)
{
    std::stringstream ss;
    for (auto it = matrix.beginHorizontal(0); it != matrix.endHorizontal(0); ++it)
    {
        ss << *it << " ";
    }
    cout << endl << ss.str() << endl;
}

TEST(Matrix, Iterators) {
    Matrix<double> matrix {2, 3};
    matrix.access(0, 0) = 0.0;
    matrix.access(0, 1) = 1.0;
    matrix.access(0, 2) = 2.0;
    matrix.access(1, 0) = 3.0;
    matrix.access(1, 1) = 4.0;
    matrix.access(1, 2) = 5.0;
    {
        std::stringstream ss;
        for (auto it = matrix.beginVertical(0); it != matrix.endVertical(0); ++it)
        {
            ss << *it << "\n";
        }
        cout << endl << ss.str() << endl;
        EXPECT_EQ(ss.str(), "0\n3\n");
    }
    {
        std::stringstream ss;
        for (auto it = matrix.beginHorizontal(0); it != matrix.endHorizontal(0); ++it)
        {
            ss << *it << " ";
        }
        cout << endl << ss.str() << endl;
        EXPECT_EQ(ss.str(), "0 1 2 ");
    }
}
