#include "SparseVector.h"
#include <iostream>

int main()
{
    SparseVector a(10);
    SparseVector b(10);

    a.setElem(2, 5);
    a.setElem(7, -3);

    b.setElem(2, 4);
    b.setElem(5, 10);

    SparseVector c = a + b;

    std::cout << c.getElem(2) << std::endl; // выдаст 9
    std::cout << c.getElem(5) << std::endl; // выдаст 10
    std::cout << c.getElem(7) << std::endl; // выдаст -3
}
