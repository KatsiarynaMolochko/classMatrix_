#include "matrix.hpp"
#include <stdexcept>
#include <iostream>


Matrix::Matrix(int rows, int columns) {
    this->columns = columns;
    this->rows = rows;

    accumulate(rows, columns);
    initDefault();
}

Matrix::Matrix(const Matrix &other) {
    rows = other.rows;
    columns = other.rows;

    accumulate(rows, columns);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = other[i][j];
        }
    }
}

Matrix::~Matrix() {
    clear();
}

Matrix &Matrix::operator=(const Matrix &other) {
    if(this == &other) {
        return *this;
    }

    if (rows != other.rows || columns != other.rows) {
        accumulate(other.rows, other.columns);
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }

    return *this;
}

const double *Matrix::operator[](int index) const {
    checkIndex(index);
    return matrix[index];
}

double *Matrix::operator[](int index) {
    checkIndex(index);
    return matrix[index];
}

double& Matrix::operator()(int row, int column) {
    checkIndex(row, column);
    return matrix[row][column];
}

double Matrix::operator()(int row, int column) const {
    checkIndex(row, column);
    return matrix[row][column];
}

Matrix operator-(const Matrix &other) {
    Matrix result(other.rows, other.columns);

    for (int i = 0; i < other.rows; ++i) {
        for (int j = 0; j < other.columns; ++j) {
            result.matrix[i][j] = (-1) * other.matrix[i][j];
        }
    }

    return result;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    Matrix::matrixSizesEqual(*this, other);

    for (int i = 0; i < other.rows; ++i) {
        for (int j = 0; j < other.columns; ++j) {
            matrix[i][j] += other.matrix[i][j];
        }
    }

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    Matrix::matrixSizesEqual(*this, other);

    for (int i = 0; i < other.rows; ++i) {
        for (int j = 0; j < other.columns; ++j) {
            matrix[i][j] -= other.matrix[i][j];
        }
    }

    return *this;
}

Matrix operator+(const Matrix &left, const Matrix &right) {
    Matrix::matrixSizesEqual(left, right);
    Matrix result(right.rows,right.columns);

    for (int i = 0; i < right.rows; ++i) {
        for (int j = 0; j < right.columns; ++j) {
            result.matrix[i][j] = right[i][j] + left[i][j];
        }
    }

    return result;
}

Matrix operator-(const Matrix &left, const Matrix &right) {
    Matrix::matrixSizesEqual(left, right);
    Matrix result(right.rows,right.columns);

    for (int i = 0; i < right.rows; ++i) {
        for (int j = 0; j < right.columns; ++j) {
            result.matrix[i][j] = right[i][j] - left[i][j];
        }
    }

    return result ;
}

Matrix operator*(const Matrix &left, const Matrix &right) {
    Matrix::canMultiply(left, right);
    Matrix result(left.rows, right.columns);

    for (int i = 0; i < left.rows; ++i) {
        for (int j = 0; j < right.columns; ++j) {
            for (int k = 0; k < left.columns; ++k) {
                result.matrix[i][j] += (left[i][k] * right[k][j]);
            }
        }
    }

    return result;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    Matrix result = *this * other;
    *this = result;
    return *this;
}

Matrix &Matrix::operator*=(const double &number) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; i < columns; ++i) {
            matrix[i][j] *= number;
        }
    }

    return *this;
}

Matrix operator*(const double &number, const Matrix &matrix) {
    return (matrix * number);
}

Matrix operator*(const Matrix &matrix, const double &number) {
    Matrix result(matrix.rows, matrix.columns);
    return (result *= number);
}

bool operator==(const Matrix &left, const Matrix &right) {
    Matrix::matrixSizesEqual(left, right);

    for (int i = 0; i < left.rows; ++i) {
        for (int j = 0; j < left.columns; ++j) {
            if (left[i][j] != right[i][j]){
                return false;
            }
        }
    }

    return true;
}

bool operator!=(const Matrix &left, const Matrix &right) {
    return !(left == right);
}

int Matrix::Rows() const {
    return rows;
}

int Matrix::Columns() const {
    return columns;
}

void Matrix::inputMatrix() {
    std::cout << std::endl << "Input matrix with size: " << rows << 'x' << columns << std::endl;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cin >> matrix[i][j];
        }
    }
}

Matrix Matrix::Identity(int size) {
    Matrix identity(size, size);

    for (int i = 0; i < size; ++i) {
        identity[i][i] = 1;
    }

    return identity;
}

Matrix Matrix::Transpose() const {
    Matrix transposed(columns, rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            transposed.matrix[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

void Matrix::accumulate(int size_n, int size_m) {
    clear();

    matrix = new double* [size_n];
    for (int i = 0; i < size_n; ++i) {
        matrix[i] = new double [size_m];
    }
}

void Matrix::initDefault() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = 0;
        }
    }
}

void Matrix::clear() {
    if (matrix != nullptr) {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = nullptr;
    }
}

void Matrix::show() const {
    std::cout << *this;
}

void Matrix::checkIndex(int index) const {
    if(index < 0 || index > rows) {
        throw std::out_of_range("out of range");
    }
}

void Matrix::checkIndex(int row, int column) const {
    if (row < 0 || column < 0 || row >= rows || column >= columns) {
        throw std::out_of_range("out of range");
    }
}

void Matrix::matrixSizesEqual(const Matrix &left, const Matrix &right) {
    if (left.columns != right.columns || left.rows != right.rows){
        throw std::out_of_range("out of range");
    }
}

void Matrix::canMultiply(const Matrix &left, const Matrix &right) {
    if (left.columns != right.rows) {
        throw std::out_of_range("out of range");
    }
}

std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
    out << "\n";
    for (int i = 0; i < matrix.Rows(); ++i) {
        for (int j = 0; j < matrix.Columns(); ++j) {
            out << matrix[i][j] << " ";
        }
        out << "\n";
    }

    return out;
}


