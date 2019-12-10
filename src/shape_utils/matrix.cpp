//
// Created by Nick Grout on 2019-12-09.
//

#include "matrix.h"

namespace map { namespace shapeutils {

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& rhs) noexcept
{
    cols = rhs.cols;
    rows = rhs.rows;
    data = std::move(rhs.data);
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
    cols = rhs.cols;
    rows = rhs.rows;
    data.reset(new T[cols*rows]);
    for (int i=0; i<cols*rows; ++i) {
        data[i] = rhs.data[i];
    }
    return *this;
}

template <typename T>
VerticalMatrixIterator<T> Matrix<T>::beginVertical(size_t col_access)
{
    return VerticalMatrixIterator<T>(&data[rows * col_access]);
}

template <typename T>
ConstVerticalMatrixIterator<T> Matrix<T>::beginVertical(size_t col_access) const
{
    return ConstVerticalMatrixIterator<T>(&data[rows * col_access]);
}

template <typename T>
VerticalMatrixIterator<T> Matrix<T>::endVertical(size_t col_access)
{
    return VerticalMatrixIterator<T>(&data[rows * col_access + rows]);
}

template <typename T>
ConstVerticalMatrixIterator<T> Matrix<T>::endVertical(size_t col_access) const
{
    return ConstVerticalMatrixIterator<T>(&data[rows * col_access + rows]);
}

template <typename T>
HorizontalMatrixIterator<T> Matrix<T>::beginHorizontal(size_t i)
{
    return HorizontalMatrixIterator<T>(&data[i], rows);
}

template <typename T>
ConstHorizontalMatrixIterator<T> Matrix<T>::beginHorizontal(size_t i) const
{
    return ConstHorizontalMatrixIterator<T>(&data[i], rows);
}

template <typename T>
HorizontalMatrixIterator<T> Matrix<T>::endHorizontal(size_t i)
{
    return HorizontalMatrixIterator<T>(&data[cols*rows + i], rows);
}

template <typename T>
ConstHorizontalMatrixIterator<T> Matrix<T>::endHorizontal(size_t i) const
{
    return ConstHorizontalMatrixIterator<T>(&data[cols*rows + i], rows);
}

template <typename T>
T& Matrix<T>::access(size_t row_access, size_t col_access)
{
    return data.get()[rows * col_access + row_access];
}

template <typename T>
const T& Matrix<T>::access(size_t row_access, size_t col_access) const
{
    return data.get()[rows * col_access + row_access];
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    if (lhs.cols != rhs.rows) {
        throw std::invalid_argument("n of matrix 1 must equal m of matrix 2");
    }
    Matrix<T> new_matrix {};
}

} // namespace shapeutils
} // namespace map
