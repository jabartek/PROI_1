#include <stdexcept>
#include <cmath>
#include <string>
#include <random>

#include "matrix.h"


using std::ostream;
using std::istream;
using std::domain_error;


Matrix::Matrix(int order) : order_((order > 0) ? order : 1) {
    allocation();
    for (int i = 0; i < order_; i++) {
        for (int j = 0; j < order_; j++) {
            cells_[i][j] = 0;
        }
    }
    std::cout << "A matrix " << this << " of order " << order << " without any parameters created\n";
}

/* Following constructor can be provided with a parameter, so a specific type of matrix will be created.
 * Parameter "1" creates identity matrix.
 * Parameter "2" fills the matrix with random values between 0 and 10*/
Matrix::Matrix(int order, char constructorParam) : order_(order) {
    allocation();
    for (int i = 0; i < order_; i++) {
        for (int j = 0; j < order_; j++) {
            if (i == j and constructorParam == 1) cells_[i][j] = 1;
            else if (constructorParam == 2) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(1, 1000);
                cells_[i][j] = double(dis(gen)) / 100;
            } else cells_[i][j] = 0;
        }
    }
    std::cout << "A matrix " << this << " of order " << order << " with parameter " << int(constructorParam)
              << " created\n";
}

Matrix::Matrix() : order_(1) {
    allocation();
    cells_[0][0] = 0;
    std::cout << "A default matrix " << this << " of order 1 created\n";
}

Matrix::~Matrix() {
    for (int i = 0; i < order_; i++) {
        delete[] cells_[i];
    }
    delete[] cells_;
    std::cout << "A matrix " << this << " of some order destructed. Sad :<\n";
}

Matrix::Matrix(const Matrix &matrix) : order_(matrix.order_) {
    allocation();
    for (int i = 0; i < order_; i++) {
        for (int j = 0; j < order_; j++) {
            cells_[i][j] = matrix.cells_[i][j];
        }
    }
    std::cout << "A matrix " << this << " of order " << order_ << " copied from "<< &matrix <<"\n";
}

Matrix &Matrix::operator=(const Matrix &matrix) {
    if (this == &matrix) {
        return *this;
    }

    if (order_ != matrix.order_) {
        for (int i = 0; i < order_; i++) {
            delete[] cells_[i];
        }
        delete[] cells_;

        order_ = matrix.order_;
        allocation();
    }

    for (int i = 0; i < order_; i++) {
        for (int j = 0; j < order_; j++) {
            cells_[i][j] = matrix.cells_[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &matrix) {
    if (order_ != matrix.order_)
        throw std::domain_error("Error: matrices of differing orders cannot be added.");
    for (int i = 0; i < order_; i++) {
        for (int j = 0; j < order_; j++) {
            cells_[i][j] += matrix.cells_[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &matrix) {
    if (order_ != matrix.order_)
        throw std::domain_error("Error: matrices of differing orders cannot be subtracted.");
    for (int i = 0; i < order_; i++) {
        for (int j = 0; j < order_; j++) {
            cells_[i][j] -= matrix.cells_[i][j];
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &matrix) {
    if (order_ != matrix.order_)
        throw std::domain_error("Error: matrices of differing orders cannot be multiplicated.");
    Matrix temp(order_);
    for (int i = 0; i < order_; i++) {
        for (int j = 0; j < order_; j++) {
            for (int k = 0; k < order_; k++) {
                temp.cells_[i][j] += (cells_[i][k] * matrix.cells_[k][j]);
            }
        }
    }
    return (*this = temp);
}

Matrix &Matrix::operator*=(double num) {
    for (int i = 0; i < order_; i++) {
        for (int j = 0; j < order_; j++) {
            cells_[i][j] *= num;
        }
    }
    return *this;
}

double Matrix::calcDet() {
    double determinant = 0;
    if (order_ == 1) determinant = cells_[0][0];
    else if (order_ == 2) {
        determinant = cells_[0][0] * cells_[1][1] - cells_[0][1] * cells_[1][0];
    } else if (order_ == 3) {
        determinant = cells_[0][0] * cells_[1][1] * cells_[2][2] - cells_[0][0] * cells_[2][1] * cells_[1][2] +
                      cells_[1][0] * cells_[2][1] * cells_[0][2] - cells_[1][0] * cells_[0][1] * cells_[2][2] +
                      cells_[2][0] * cells_[0][1] * cells_[1][2] - cells_[2][0] * cells_[1][1] * cells_[0][2];
    } else {
        Matrix sourceCopy(*this);
        if (sourceCopy.cells_[0][0] == 0) {
            for (int i = 1; i < sourceCopy.order_; i++) {
                if (sourceCopy.cells_[0][i] != 0) {
                    sourceCopy.swapRows(0, i);
                    break;
                }
            }
        }
        if (sourceCopy.cells_[0][0] == 0) return 0;
        Matrix newMinor(order_ - 1);
        for (int i = 1; i < order_; i++) {
            for (int j = 1; j < order_; j++) {
                newMinor.cells_[i - 1][j - 1] = sourceCopy.cells_[0][0] * sourceCopy.cells_[i][j] -
                                                sourceCopy.cells_[i][0] * sourceCopy.cells_[0][j];
            }
        }
        determinant = newMinor.calcDet() / (pow(sourceCopy.cells_[0][0], order_ - 2));
    }
    return determinant;
}

void Matrix::swapRows(int row1, int row2) {
    double *temp = cells_[row1];
    cells_[row1] = cells_[row2];
    cells_[row2] = temp;
}

void Matrix::allocation() {
    cells_ = new double *[order_];
    for (int i = 0; i < order_; i++) {
        cells_[i] = new double[order_];
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
    for (int i = 0; i < matrix.order_; i++) {
        for (int j = 0; j < matrix.order_; j++) {
            outputStream << matrix.cells_[i][j] << " ";
        }
        outputStream << "\n";
    }
    return outputStream;
}

istream &operator>>(std::istream &inputStream, Matrix &matrix) {
    for (int i = 0; i < matrix.order_; i++) {
        for (int j = 0; j < matrix.order_; j++) {
            std::string temp;
            double number = 0;
            bool error = false;
            do {
                std::cin >> temp;
                try {
                    number = std::stod(temp);
                    error = false;
                }
                catch (std::invalid_argument) {
                    std::cout << "\nInvalid input at x = " << i << ", y = " << j << " Try again: ";
                    error = true;
                }
            } while (error);
            matrix.cells_[i][j] = number;
        }
    }
    return inputStream;
}

