# Image Processing Library

A custom image processing library built in C++ using object-oriented design principles. This project implements pixel-level image operations through an inheritance-based class hierarchy, with manual memory management handled by a custom templated Vector class.

## Features

- Load and save PNG images
- Pixel-wise arithmetic operations: addition, subtraction, dot product
- Scalar multiplication (brightness scaling)
- Image resizing
- Custom templated Vector and Matrix base classes with full operator overloading

## Project Structure

├── main.cpp        # Entry point and CLI interface
├── Image.h/.cpp    # Image class (extends Matrix)
├── Matrix.h/.cpp   # Matrix base class
├── Vector.h        # Templated Vector class with manual memory management
├── Makefile        # Build configuration
└── stb_image*.h    # Third-party image loading/writing/resizing headers

## Dependencies

- stb_image (https://github.com/nothings/stb) — single-header image loading, writing, and resizing

## How to Compile

make

Or manually:

g++ -std=c++17 -o program main.cpp Image.cpp Matrix.cpp

## Usage

./program <function> <input1> <input2 or scale factor> <output_directory>

### Functions

Function   | Description                          | Example
add        | Add two images pixel-wise            | ./program add img1.png img2.png output/
subtract   | Subtract two images pixel-wise       | ./program subtract img1.png img2.png output/
dot        | Multiply two images pixel-wise       | ./program dot img1.png img2.png output/
scale      | Resize image by a scale factor       | ./program scale img1.png 0.5 output/

Output is saved as output.png in the specified directory.

## Concepts Demonstrated

- Object-oriented programming in C++
- Class inheritance and operator overloading
- Template classes and generic programming
- Manual memory management (heap allocation, deep copy, destructor)
- File I/O and third-party library integration
