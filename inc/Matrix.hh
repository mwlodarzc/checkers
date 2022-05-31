#ifndef MATRIX_2D_HH
#define MATRIX_2D_HH

template <typename T>
class Matrix2D
{
private:
    T *data;

public:
    Matrix2D(int size) : data(new Matrix2D<T>[2 * size]) {}
    ~Matrix2D() { delete data; }
    T &operator[][](int i)
};

#endif