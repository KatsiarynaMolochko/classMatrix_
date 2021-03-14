#include <iostream>
#include "matrix.hpp"

int main(){
    Matrix obj(4, 8);
    Matrix obj2 (5,7);
    Matrix obj3(2,3);
    Matrix obj4(3,5);
    Matrix obj7(5,5);

    obj3.inputMatrix();
    obj4.inputMatrix();

    Matrix obj5 = obj3 * obj4;
    obj5.show();
    std::cout << obj5 << std::endl;

    std::cout << obj.Rows() << std::endl;
    std::cout << obj5.Columns() << std::endl;

    try {
        obj[-5][-10];
    }
    catch (const std::out_of_range& error) {
        std::cout << std::endl;
        std::cerr << "ERROR: Index can't be a negative number." << error.what() << std::endl;
    }

    try {
       obj2 *= obj;
       Matrix objM1 = obj2 * obj;
       std::cout << obj2 << std::endl;
       std::cout << objM1 << std::endl;
    }
    catch (const std::out_of_range& error) {
        std::cout << std::endl;
        std::cerr << "ERROR: Matrices of this size cannot be multiplied. " << error.what() << std::endl;
    }

    try {
        Matrix objX = obj - obj2;
        std::cout << objX << std::endl;
        obj -= obj;
        Matrix objY = obj2 + obj;
        std::cout << objY << std::endl;
        obj += obj2;
    }
    catch (const std::out_of_range& error) {
        std::cout << std::endl;
        std::cerr << "ERROR: Matrices have different sizes" << error.what() << std::endl;
    }

    try {
        obj2(1, 1) = 5;
        std::cout << obj2 << std::endl;

        obj7(2, 3) = 1;
        std::cout << obj7 << std::endl;

        obj3(100, 100) = 5;
        std::cout << obj3  << std::endl;
    }
    catch (const std::out_of_range& error) {
        std::cout << std::endl;
        std::cerr << "ERROR: Index out of matrix range" << error.what() << std::endl;
    }

    try {
        Matrix transp = obj2.Transpose();
        std::cout << transp << std::endl;
    }
    catch (const std::out_of_range& error) {
        std::cout << std::endl;
        std::cerr << "Unexpected error" << error.what() << std::endl;
    }

    try {
        Matrix x = Matrix::Identity(5);
        std::cout << x << std::endl;

        std::cout << x * x * x << std::endl;
        std::cout << x + x + x << std::endl;
        std::cout << x * x + x << std::endl;
    }
    catch (const std::out_of_range& error) {
        std::cout << std::endl;
        std::cerr << "Unexpected error" << error.what() << std::endl;
    }

    return 0;
}
