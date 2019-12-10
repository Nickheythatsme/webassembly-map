//
// Created by Nick Grout on 2019-12-09.
//

#include "vector.h"
#include <memory>
#include <ostream>
#include <exception>

#ifndef MAP_SHAPE_UTILS_MATRIX_H_
#define MAP_SHAPE_UTILS_MATRIX_H_

namespace map { namespace shapeutils {

template<typename T>
class MatrixIterator;
template<typename T>
class VerticalMatrixIterator;
template<typename T>
class HorizontalMatrixIterator;
template<typename T>
class ConstHorizontalMatrixIterator;
template<typename T>
class ConstVerticalMatrixIterator;

template<typename T>
class Matrix
{
public:
    Matrix() = delete;
    // Create a new mxn matrix where M is rows and N is columns
    Matrix(size_t rows, size_t cols) :
        cols(cols), rows(rows),
        data(new T[cols*rows])
    {
        //memset(data.get(), 0x0, rows*cols*sizeof(T));
        for (int i=0; i<rows*cols; ++i) {
            data[i] = 0.0;
        }
    }
    Matrix(Matrix<T> &&rhs) noexcept :
        cols(rhs.cols), rows(rhs.rows),
        data(std::move(rhs.data))
    {
    }
    Matrix(const Matrix<T> &rhs) :
        cols(rhs.cols), rows(rhs.rows),
        data(new T[cols*rows])
    {
        memcpy(data.get(), rhs.data.get(), cols*rows);
    }
    ~Matrix() = default;
    Matrix<T>& operator=(Matrix<T>&& rhs) noexcept;
    Matrix<T>& operator=(const Matrix<T>& rhs);
    T& access(size_t row_access, size_t col_access);
    const T& access(size_t row_access, size_t col_access) const;
    // Iterators
    VerticalMatrixIterator<T> beginVertical(size_t col_access);
    ConstVerticalMatrixIterator<T> beginVertical(size_t col_access) const;
    VerticalMatrixIterator<T> endVertical(size_t col_access);
    ConstVerticalMatrixIterator<T> endVertical(size_t col_access) const;
    HorizontalMatrixIterator<T> beginHorizontal(size_t i);
    ConstHorizontalMatrixIterator<T> beginHorizontal(size_t i) const;
    HorizontalMatrixIterator<T> endHorizontal(size_t i);
    ConstHorizontalMatrixIterator<T> endHorizontal(size_t i) const;
    // Multiplication
    friend Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& rhs)
    {
        for (int i=0; i<rhs.rows; ++i) {
            for (int j=0; j<rhs.cols; ++j) {
                out << rhs.data[i*rhs.rows + j] << " ";
            }
            out << '\n';
        }
        return out;
    }
protected:
    size_t cols;
    size_t rows;
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
        const T& const_dereference() const
        {
            return *p;
        }
    protected:
        virtual void increment() = 0;
        T* p;
    private:
};

template<typename T>
class VerticalMatrixIterator: public MatrixIterator<T>
{
    public:
        explicit VerticalMatrixIterator(T *p) :
            MatrixIterator<T>(p)
        {}
        VerticalMatrixIterator(const VerticalMatrixIterator<T> &rhs) = default;
        VerticalMatrixIterator(VerticalMatrixIterator<T> &&rhs) = default;
        VerticalMatrixIterator<T>& operator++()
        {
            increment();
            return *this;
        }
        const VerticalMatrixIterator<T> operator++(int)
        {
            VerticalMatrixIterator<T> tmp(*this);
            increment();
            return tmp;
        }
        bool operator==(const VerticalMatrixIterator<T>& rhs) const
        {
            return MatrixIterator<T>::equal(rhs);
        }
        bool operator!=(const VerticalMatrixIterator<T>& rhs) const
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
class ConstVerticalMatrixIterator: public VerticalMatrixIterator<T>
{
    public:
        explicit ConstVerticalMatrixIterator(T *p) :
            VerticalMatrixIterator<T>(p)
        {}
        ConstVerticalMatrixIterator(const ConstVerticalMatrixIterator<T> &rhs) = default;
        ConstVerticalMatrixIterator(ConstVerticalMatrixIterator<T> &&rhs) = default;
        const T& operator*() const
        {
            return MatrixIterator<T>::const_dereference();
        }
    protected:
    private:
};

template<typename T>
class HorizontalMatrixIterator: public MatrixIterator<T>
{
    public:
        explicit HorizontalMatrixIterator(T *p, size_t rows) :
            rows(rows),
            MatrixIterator<T>(p)
        {}
        HorizontalMatrixIterator(const HorizontalMatrixIterator<T> &rhs) = default;
        HorizontalMatrixIterator(HorizontalMatrixIterator<T> &&rhs) noexcept = default;
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
            MatrixIterator<T>::p += rows;
        }
    private:
        size_t rows;
};

template<typename T>
class ConstHorizontalMatrixIterator: public HorizontalMatrixIterator<T>
{
    public:
        explicit ConstHorizontalMatrixIterator(T *p, size_t rows) :
            HorizontalMatrixIterator<T>(p, rows)
        {}
        ConstHorizontalMatrixIterator(const ConstHorizontalMatrixIterator<T> &rhs) = default;
        ConstHorizontalMatrixIterator(ConstHorizontalMatrixIterator<T> &&rhs) noexcept = default;
        const T& operator*() const
        {
            return MatrixIterator<T>::const_dereference();
        }
    protected:
    private:
};

} // namespace shapeutils
} // namespace map

#include "matrix.cpp"
#endif // MAP_SHAPE_UTILS_MATRIX_H_
