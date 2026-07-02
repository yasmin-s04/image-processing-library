// Vector.h

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* elements;
    int size;

public:
    // Default constructor
    Vector() : elements(nullptr), size(0) {}

    // Constructor with size
    Vector(int size) : size(size) {
        elements = new T[size];
        for (int i = 0; i < size; ++i) elements[i] = T();
    }

    // Copy constructor
    Vector(const Vector& other) : size(other.size) {
        elements = new T[size];
        for (int i = 0; i < size; ++i)
            elements[i] = other.elements[i];
    }

    // Assignment operator
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] elements;
            size = other.size;
            elements = new T[size];
            for (int i = 0; i < size; ++i)
                elements[i] = other.elements[i];
        }
        return *this;
    }

    // Destructor
    ~Vector() {
        delete[] elements;
    }

    // Return size
    int getSize() const {
        return size;
    }

    // Indexing operator
    T& operator[](int index) {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of bounds");
        return elements[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of bounds");
        return elements[index];
    }

    // Addition
    Vector operator+(const Vector& other) const {
        if (size != other.size)
            throw std::invalid_argument("Vector sizes must match for addition");
        Vector result(size);
        for (int i = 0; i < size; ++i)
            result[i] = elements[i] + other[i];
        return result;
    }

    // Subtraction
    Vector operator-(const Vector& other) const {
        if (size != other.size)
            throw std::invalid_argument("Vector sizes must match for subtraction");
        Vector result(size);
        for (int i = 0; i < size; ++i)
            result[i] = elements[i] - other[i];
        return result;
    }

    // Scalar multiplication
    Vector operator*(T scalar) const {
        Vector result(size);
        for (int i = 0; i < size; ++i)
            result[i] = elements[i] * scalar;
        return result;
    }

    // Input stream operator
    friend std::istream& operator>>(std::istream& in, Vector& v) {
        for (int i = 0; i < v.size; ++i)
            in >> v.elements[i];
        return in;
    }

    // Output stream operator
    friend std::ostream& operator<<(std::ostream& out, const Vector& v) {
        for (int i = 0; i < v.size; ++i)
            out << v.elements[i] << " ";
        return out;
    }
};

#endif // VECTOR_H


