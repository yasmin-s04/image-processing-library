// Matrix.cpp

#include "Matrix.h"
#include <stdexcept>

// Default constructor
Matrix::Matrix() {}

// Constructor with rows and columns
Matrix::Matrix(int rows, int cols) {
    data = Vector<Vector<uint8_t>>(rows);
    for (int i = 0; i < rows; ++i) {
        data[i] = Vector<uint8_t>(cols);
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& other) {
    data = other.data;
}
// Assignment operator
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        data = other.data;
    }
    return *this;
}

// Destructor
Matrix::~Matrix() {
    // No manual deallocation needed if Vector handles memory
}

// Input stream operator
std::istream& operator>>(std::istream& in, Matrix& mat) {
    int rows, cols;
    in >> rows >> cols;
    mat = Matrix(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            in >> mat[i][j];
    return in;
}

// Output stream operator
std::ostream& operator<<(std::ostream& out, const Matrix& mat) {
    int rows = mat.getRows();
    int cols = mat.getCols();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            out << (int)mat[i][j] << " ";
        out << '\n';
    }
    return out;
}

int Matrix::getRows() const {
    return data.getSize();
}

int Matrix::getCols() const {
    return data.getSize() > 0 ? data[0].getSize() : 0;
}

// Arithmetic operators
Matrix Matrix::operator+(const Matrix& other) const {
    if (getRows() != other.getRows() || getCols() != other.getCols())
        throw std::invalid_argument("Matrix dimensions must match for addition");

    Matrix result(getRows(), getCols());
    for (int i = 0; i < getRows(); ++i)
        for (int j = 0; j < getCols(); ++j)
            result[i][j] = data[i][j] + other[i][j];

    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (getRows() != other.getRows() || getCols() != other.getCols())
        throw std::invalid_argument("Matrix dimensions must match for subtraction");

    Matrix result(getRows(), getCols());
    for (int i = 0; i < getRows(); ++i)
        for (int j = 0; j < getCols(); ++j)
            result[i][j] = data[i][j] - other[i][j];

    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (getCols() != other.getRows())
        throw std::invalid_argument("Matrix dimensions must align for multiplication");

    Matrix result(getRows(), other.getCols());
    for (int i = 0; i < getRows(); ++i)
        for (int j = 0; j < other.getCols(); ++j) {
            uint8_t sum = 0;
            for (int k = 0; k < getCols(); ++k)
                sum += data[i][k] * other[k][j];
            result[i][j] = sum;
        }

    return result;
}

// Subscript operator
Vector<uint8_t>& Matrix::operator[](int index) {
    return data[index];
}

const Vector<uint8_t>& Matrix::operator[](int index) const {
    return data[index];
}

// Transpose function extra credit
void Matrix::transpose() {
    int rows = getRows();
    int cols = getCols();
    Matrix transposed(cols, rows);  // swapped dims

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            transposed[j][i] = data[i][j];

    *this = transposed;  // assign to current matrix
}
