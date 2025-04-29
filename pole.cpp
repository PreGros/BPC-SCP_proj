#include <stdio.h>
#include <stdlib.h>
#include "pole.hpp"
#include <iostream>
#include <cmath>
#include <string.h>
#include <sstream>
#include <vector>
#include <fstream>

int main(int argc, char const *argv[])
{
    int delka = 3;
    double *p2 = new double[delka];
    p2[0] = 1.0;
    p2[1] = 5.4;
    p2[2] = 10.0;
    
    Pole<double> A(delka, p2);

    delete[] p2;

    std::cout << A << std::endl;




    std::ifstream fileB;
    Pole<double> B;

    fileB.open(argv[1]);

    fileB >> B;

    Pole<double> C = A + B;


    std::cout << C << std::endl;


    return 0;
}
