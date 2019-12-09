//
// Created by Nick Grout on 2019-12-09.
//

#include "matrix.h"

namespace map { namespace shapeutils {

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& rhs) noexcept
{
    n = rhs.n;
    m = rhs.m;
    data = std::move(rhs.data);
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs)
{
    n = rhs.n;
    m = rhs.m;
    data.reset(new T[n*m]);
    for (int i=0; i<n*m; ++i) {
        data[i] = rhs.data[i];
    }
    return *this;
}

template <typename T>
VerticleMatrixIterator<T> Matrix<T>::beginVerticle(size_t n_access)
{
    return VerticleMatrixIterator<T>(&data[m * n_access]);
}

template <typename T>
VerticleMatrixIterator<T> Matrix<T>::endVerticle(size_t n_access)
{
    return VerticleMatrixIterator<T>(&data[m * n_access + m]);
}

template <typename T>
HorizontalMatrixIterator<T> Matrix<T>::beginHorizontal(size_t i)
{
    return HorizontalMatrixIterator<T>(&data[i], m);
}

template <typename T>
HorizontalMatrixIterator<T> Matrix<T>::endHorizontal(size_t i)
{
    return HorizontalMatrixIterator<T>(&data[n*m + i], m);
}

template <typename T>
T& Matrix<T>::access(size_t n_access, size_t m_access)
{
    return data.get()[n_access * m + m_access];
}

template <typename T>
const T& Matrix<T>::access(size_t n_access, size_t m_access) const
{
    return data.get()[n_access * m + m_access];
}

} // namespace shapeutils
} // namespace map
