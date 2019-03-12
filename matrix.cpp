#include <stdexcept>
#include <cmath>
#include <random>

#include "matrix.h"


using std::ostream;
using std::istream;
using std::domain_error;


Matrix::Matrix(int order) : matrixOrder(order) {
    allocation();
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            values[i][j] = 0;
        }
    }
    std::cout << "A matrix " << this << " of order " << order << " without any parameters created\n";
}

Matrix::Matrix(int order, char constructorParam) : matrixOrder(order) {
    allocation();
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            if (i == j and constructorParam == 1) values[i][j] = 1;
            else if (constructorParam == 2) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1, 1000);
                values[i][j] = double(dis(gen)) / 100;
            } else values[i][j] = 0;
        }
    }
    std::cout << "A matrix " << this << " of order " << order << " with parameter " << int(constructorParam)
              << " created\n";
}

Matrix::Matrix() : matrixOrder(1) {
    allocation();
    values[0][0] = 0;
    std::cout << "A default matrix " << this << " of order 1 created\n";
}

Matrix::~Matrix() {
    for (int i = 0; i < matrixOrder; i++) {
        delete[] values[i];
    }
    delete[] values;
    std::cout << "A matrix " << this << " of some order destructed. Sad :<\n";
}

Matrix::Matrix(const Matrix &matrix) : matrixOrder(matrix.matrixOrder) {
    allocation();
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            values[i][j] = matrix.values[i][j];
        }
    }
    std::cout << "A matrix " << this << " of order " << matrixOrder << " copied\n";
}

Matrix &Matrix::operator=(const Matrix &matrix) {
    if (this == &matrix) {
        return *this;
    }

    if (matrixOrder != matrix.matrixOrder) {
        for (int i = 0; i < matrixOrder; i++) {
            delete[] values[i];
        }
        delete[] values;

        matrixOrder = matrix.matrixOrder;
        allocation();
    }

    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            values[i][j] = matrix.values[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &matrix) {
    int smallerOrder;
    if (matrixOrder > matrix.matrixOrder) smallerOrder = matrix.matrixOrder;
    else smallerOrder = matrixOrder;
    for (int i = 0; i < smallerOrder; i++) {
        for (int j = 0; j < smallerOrder; j++) {
            values[i][j] += matrix.values[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &matrix) {
    int smallerOrder;
    if (matrixOrder > matrix.matrixOrder) smallerOrder = matrix.matrixOrder;
    else smallerOrder = matrixOrder;
    for (int i = 0; i < smallerOrder; i++) {
        for (int j = 0; j < smallerOrder; j++) {
            values[i][j] -= matrix.values[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &matrix) {
    if (matrixOrder != matrix.matrixOrder)
        throw std::domain_error("Error: matrices of differing orders cannot be multiplicated.");
    Matrix temp(matrixOrder);
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            for (int k = 0; k < matrixOrder; k++) {
                temp.values[i][j] += (values[i][k] * matrix.values[k][j]);
            }
        }
    }
    return (*this = temp);
}

Matrix &Matrix::operator*=(double num) {
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            values[i][j] *= num;
        }
    }
    return *this;
}

double Matrix::calcDet() {
    double determinant = 0;
    if (matrixOrder == 1) determinant = values[0][0];
    else if (matrixOrder == 2) {
        determinant = values[0][0] * values[1][1] - values[0][1] * values[1][0];
    } else if (matrixOrder == 3) {
        determinant = values[0][0] * values[1][1] * values[2][2] - values[0][0] * values[2][1] * values[1][2] +
                      values[1][0] * values[2][1] * values[0][2] - values[1][0] * values[0][1] * values[2][2] +
                      values[2][0] * values[0][1] * values[1][2] - values[2][0] * values[1][1] * values[0][2];
    } else {
        Matrix sourceCopy(*this);
        if (sourceCopy.values[0][0] == 0) {
            for (int i = 1; i < sourceCopy.matrixOrder; i++) {
                if (sourceCopy.values[0][i] != 0) {
                    sourceCopy.swapRows(0, i);
                    break;
                }
            }
        }
        if (sourceCopy.values[0][0] == 0) return 0;
        Matrix newMinor(matrixOrder - 1);
        for (int i = 1; i < matrixOrder; i++) {
            for (int j = 1; j < matrixOrder; j++) {
                newMinor.values[i - 1][j - 1] = sourceCopy.values[0][0] * sourceCopy.values[i][j] -
                                                sourceCopy.values[i][0] * sourceCopy.values[0][j];
            }
        }
        determinant = newMinor.calcDet() / (pow(sourceCopy.values[0][0], matrixOrder - 2));
    }
    return determinant;
}

void Matrix::swapRows(int row1, int row2) {
    double *temp = values[row1];
    values[row1] = values[row2];
    values[row2] = temp;
}

void Matrix::allocation() {
    values = new double *[matrixOrder];
    for (int i = 0; i < matrixOrder; i++) {
        values[i] = new double[matrixOrder];
    }
}


Matrix operator+(const Matrix &matrix1, const Matrix &matrix2) {
    Matrix temp(matrix1);
    return (temp += matrix2);
}

Matrix operator-(const Matrix &matrix1, const Matrix &matrix2) {
    Matrix temp(matrix1);
    return (temp -= matrix2);
}

Matrix operator*(const Matrix &matrix1, const Matrix &matrix2) {
    Matrix temp(matrix1);
    return (temp *= matrix2);
}

Matrix operator*(const Matrix &matrix, double num) {
    Matrix temp(matrix);
    return (temp *= num);
}

Matrix operator*(double num, const Matrix &matrix) {
    return (matrix * num);
}

std::ostream &operator<<(std::ostream &outputStream, const Matrix &matrix) {
    for (int i = 0; i < matrix.matrixOrder; i++) {
        for (int j = 0; j < matrix.matrixOrder; j++) {
            outputStream << matrix.values[i][j] << " ";
        }
        outputStream << "\n";
    }
    return outputStream;
}

istream &operator>>(std::istream &inputStream, Matrix &matrix) {
    for (int i = 0; i < matrix.matrixOrder; i++) {
        for (int j = 0; j < matrix.matrixOrder; j++) {
            inputStream >> matrix.values[i][j];
        }
    }
    return inputStream;
}