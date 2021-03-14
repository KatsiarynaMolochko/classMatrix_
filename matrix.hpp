#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <iostream>

class Matrix {
public:
    Matrix() = delete;
    Matrix(int rows, int columns);
    Matrix(const Matrix& other);
    ~Matrix();
    Matrix& operator=(const Matrix& other);


    double* operator[](int index);  // может выбросить исключение
    const double* operator[](int index) const;  // может выбросить исключение

    double& operator()(int row, int column);  // может выбросить исключение
    double operator()(int row, int column) const;

    friend Matrix operator-(const Matrix& other);  // унарный оператор

    Matrix& operator+=(const Matrix& other);  // может выбросить исключение
    Matrix& operator-=(const Matrix& other);  // может выбросить исключение
    Matrix& operator*=(const Matrix& other);  // может выбросить исключение
    Matrix& operator*=(const double& number);

    friend bool operator==(const Matrix& left, const Matrix& right);
    friend bool operator!=(const Matrix& left, const Matrix& right);

    friend Matrix operator*(const double& number, const Matrix& matrix);
    friend Matrix operator*(const Matrix& matrix, const double& number);

    friend Matrix operator+(const Matrix& left, const Matrix& right);  // могут выбросить исключение
    friend Matrix operator-(const Matrix& left, const Matrix& right);  // могут выбросить исключение
    friend Matrix operator*(const Matrix& left, const Matrix& right);  // могут выбросить исключение

    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix);

    int Rows() const;
    int Columns() const;

    [[nodiscard]] Matrix Transpose() const;  // транспонированная матрица

    static Matrix Identity(int size);  // единичная матрица
    void show() const;
    void inputMatrix();

    static void canMultiply(const Matrix &left, const Matrix &right);
    static void matrixSizesEqual(const Matrix& left, const Matrix& right);

private:
    double** matrix = nullptr;
    int rows, columns;

    void accumulate( int size_n, int size_m);
    void clear();
    void initDefault();
    void checkIndex(int index) const;
    void checkIndex(int row, int column) const;
};

#endif
