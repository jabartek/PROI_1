#ifndef PROI_1_MATRIX
#define PROI_1_MATRIX


#include <iostream>

class Matrix {
public:
    explicit Matrix(int);

    Matrix(int, char);

    Matrix();

    ~Matrix();

    Matrix(const Matrix &);

    Matrix &operator=(const Matrix &);

    Matrix &operator+=(const Matrix &);

    Matrix &operator-=(const Matrix &);

    Matrix &operator*=(const Matrix &);

    Matrix &operator*=(double);

    friend std::ostream &operator<<(std::ostream &, const Matrix &);

    friend std::istream &operator>>(std::istream &, Matrix &);

    double calcDet();

    void swapRows(int, int);

private:
    int matrixOrder;
    double **values;

    void allocation();
};

Matrix operator+(const Matrix &, const Matrix &);

Matrix operator-(const Matrix &, const Matrix &);

Matrix operator*(const Matrix &, const Matrix &);

Matrix operator*(const Matrix &, double);

Matrix operator*(double, const Matrix &);


#endif //PROI_1_MATRIX
