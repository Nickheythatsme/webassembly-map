//
// Created by Nick Grout on 2019-12-09.
//

#include "vector.h"
#include <memory>
#include <ostream>

#ifndef MAP_SHAPE_UTILS_MATRIX_H_
#define MAP_SHAPE_UTILS_MATRIX_H_

namespace map { namespace shapeutils {

template<typename T>
class MatrixIterator;
template<typename T>
class VerticleMatrixIterator;
template<typename T>
class HorizontalMatrixIterator;

template<typename T>
class Matrix
{
public:
    Matrix() = delete;
    Matrix(size_t n, size_t m) :
        n(n), m(m),
        data(new T[n*m])
    {
        for (int i=0; i<n*m; ++i) {
            data[i] = 0.0;
        }
    }
    Matrix(Matrix<T> &&rhs) noexcept :
        n(rhs.n), m(rhs.m),
        data(std::move(rhs.data))
    {
    }
    Matrix(const Matrix<T> &rhs) :
        n(rhs.n), m(rhs.m),
        data(new T[n*m])
    {
        memcpy(data.get(), rhs.data.get(), n*m);
    }
    ~Matrix() = default;
    Matrix<T>& operator=(Matrix<T>&& rhs) noexcept;
    Matrix<T>& operator=(const Matrix<T>& rhs);
    T& access(size_t n_access, size_t m_access);
    const T& access(size_t n_access, size_t m_access) const;
    VerticleMatrixIterator<T> beginVerticle(size_t i);
    VerticleMatrixIterator<T> endVerticle(size_t i);
    HorizontalMatrixIterator<T> beginHorizontal(size_t i);
    HorizontalMatrixIterator<T> endHorizontal(size_t i);
    friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& rhs)
    {
        for (int current_m=0; current_m< rhs.m; ++current_m) {
            for (int current_n=0; current_n < rhs.n; ++current_n) {
                out << rhs.data[current_n*rhs.m + current_m] << " ";
            }
            out << std::endl;
        }
        return out;
    }
protected:
    size_t n;
    size_t m;
    std::unique_ptr<T[]> data;
private:
};


template<typename T>
class MatrixIterator: public std::iterator<std::input_iterator_tag, T>
{
    public:
        MatrixIterator() = delete;
        explicit MatrixIterator(T *p):
            p(p)
        {}
        bool equal(const MatrixIterator<T> &rhs) const
        {
            return p == rhs.p;
        }
        T& dereference()
        {
            return *p;
        }
    protected:
        virtual void increment() = 0;
        T* p;
    private:
};

template<typename T>
class VerticleMatrixIterator: MatrixIterator<T>
{
    public:
        explicit VerticleMatrixIterator(T *p) :
            MatrixIterator<T>(p)
        {}
        VerticleMatrixIterator(const VerticleMatrixIterator<T> &rhs):
            MatrixIterator<T>(rhs.p)
        {}
        VerticleMatrixIterator<T>& operator++()
        {
            increment();
            return *this;
        }
        const VerticleMatrixIterator<T> operator++(int)
        {
            VerticleMatrixIterator<T> tmp(*this);
            increment();
            return tmp;
        }
        bool operator==(const VerticleMatrixIterator<T>& rhs) const
        {
            return MatrixIterator<T>::equal(rhs);
        }
        bool operator!=(const VerticleMatrixIterator<T>& rhs) const
        {
            return !MatrixIterator<T>::equal(rhs);
        }
        T& operator*()
        {
            return MatrixIterator<T>::dereference();
        }
    protected:
        void increment()
        {
            ++MatrixIterator<T>::p;
        }
    private:
};

template<typename T>
class HorizontalMatrixIterator: MatrixIterator<T>
{
    public:
        explicit HorizontalMatrixIterator(T *p, size_t n) :
            n(n),
            MatrixIterator<T>(p)
        {}
        HorizontalMatrixIterator(const HorizontalMatrixIterator<T> &rhs):
            n(rhs.n),
            MatrixIterator<T>(rhs.p)
        {}
        HorizontalMatrixIterator<T>& operator++()
        {
            increment();
            return *this;
        }
        const HorizontalMatrixIterator<T> operator++(int)
        {
            HorizontalMatrixIterator<T> tmp(*this);
            increment();
            return tmp;
        }
        bool operator==(const HorizontalMatrixIterator<T>& rhs) const
        {
            return MatrixIterator<T>::equal(rhs);
        }
        bool operator!=(const HorizontalMatrixIterator<T>& rhs) const
        {
            return !MatrixIterator<T>::equal(rhs);
        }
        T& operator*()
        {
            return MatrixIterator<T>::dereference();
        }
    protected:
        void increment()
        {
            MatrixIterator<T>::p += n;
        }
    private:
        size_t n;
};

} // namespace shapeutils
} // namespace map

#include "matrix.cpp"
#endif // MAP_SHAPE_UTILS_MATRIX_H_
