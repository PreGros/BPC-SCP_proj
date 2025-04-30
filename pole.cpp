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
    int delka = 5;
    double *p2 = new double[delka];
    p2[0] = 0.5;
    p2[1] = 5.0;
    p2[2] = 10.0;
    p2[3] = 25.0;
    p2[4] = 150.0;
    
    Pole<double> A(delka, p2);

    delete[] p2;




    std::ifstream fileB;
    Pole<double> B;

    fileB.open(argv[1]);

    fileB >> B;

    Pole<double> C = B / A;
    
    std::cout << C << std::endl;


    return 0;
}
